//-----------------------------------------------------------------------------
//
// Title:			ds30 Loader GUI
//
// Copyright:		Copyright © 08-09, Mikael Gustafsson
//
// Version:			1.3.4 january 2010
//
// Link:			http://mrmackey.no-ip.org/elektronik/ds30loader/
//
// History:			1.3.4 Settings are remebered for each different file opened
//                        Added possibility to use custom bootloader placement and size                  
//                  1.3.3 Fixed bug not able to open terminal until download or check for bl was done first
//                        Improved code for reparse of hex-file when window is activated
//                        Improved about window
//                        Improved check for version window
//                        Improved info output
//                        New graphical hex-file representation
//                  1.3.2 Fixed crash on Linux when settings.xml was present
//                  1.3.1 Fixed redraw bug that only showed up in xp using xp style visual theme
//                  1.3.0 Hex-file is reloaded (if needed) when window is activated
//                        Simple serial terminal emulator added
//                        Option to reset all settings to default
//                        New simple/advanced mode to not intimidate new users/beginners
//                  1.2.2 Settings are stored as xml (again)
//                        Process priority is raised during download if polltime is < 100ms
//                        Added Aboutbox
//                        Reworked check version and update, includes a new window on help menu
//                        More compact design
//                        Output textbox can be hidden
//                  1.2.1 Added check for new version on startup option
//                        Check for new version is improved
//                  1.2.0 Added device reset, decvice activation and time options
//                  1.1.0 Changes reflecting new ds30 Loader version
//                  1.0.4 Some improvements in clsSerialPort
//                        GUI and actual bootloader code is now separated
//                        clsSerialport and debugtext moved to separate helper library
//                  1.0.2 Added debugmode
//                        Added micro mode
//                        Added menuitems with shortcut keys
//                  1.0.1 Added check for latest version
//					0.9.7 Better error handling
//						  Remembers all settings now					
//					0.9.3 Application remebers settings now
//					0.9.2 Overall time performance ~65% faster						  
//						  Better debug output
//						  Abort button fixed
//					0.9.1 Added "check for bootloader" button
//					0.9.0 Initial release
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//    This file is part of ds30 Loader GUI.
//
//    ds30 Loader GUI is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation.
//
//    ds30 Loader GUI is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with ds30 Loader GUI.  If not, see <http://www.gnu.org/licenses/>.
//-----------------------------------------------------------------------------    

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Collections;
using System.Xml;
using System.Xml.Serialization;
using System.IO;
using System.Runtime.InteropServices;
using System.Net;
using GHelper;
using ds30Loader;


namespace ds30_Loader_GUI
{
	//-------------------------------------------------------------------------
	// Class: frmDS30Loader
	//-------------------------------------------------------------------------
	public partial class frmDS30Loader : Form
	{
		//---------------------------------------------------------------------
		// Public constants
		//---------------------------------------------------------------------	
		public const string strHexFileFilter = "Hex file|*.hex|All files (*.*)|*.*";
        public const string strURLHomepage = "http://mrmackey.no-ip.org/elektronik/ds30loader/";        
        private const string strVersion = "1.3.4";
        static public Version verGUI = null;

        // Used for dragging form without caption bar, windows only
        public const int WM_NCLBUTTONDOWN = 0xA1;
        public const int HT_CAPTION = 0x2;
        [DllImportAttribute("user32.dll")]
        public static extern int SendMessage(IntPtr hWnd, int Msg, int wParam, int lParam);
        [DllImportAttribute("user32.dll")]
        public static extern bool ReleaseCapture();

		
		//---------------------------------------------------------------------
		// Variables
		//---------------------------------------------------------------------	
		private clsSerialPort objPort = null;		
        private Size sizeBeforeMicro;
        private clsSettings objSettings = null;
        private clsHex objHex = null;
        private clsDownloadSettings objds30LSettings = null;
        private clsRecentFiles objRecentFiles = null;
		private bool bStartup = true;

				
		//---------------------------------------------------------------------
		// Constructor()
		//---------------------------------------------------------------------	
		public frmDS30Loader()
		{
			bStartup = true;
            InitializeComponent();

            //---------------------------------------------------------------------	
            // Create objects
            //---------------------------------------------------------------------	
            verGUI = new Version( strVersion );            
            sizeBeforeMicro = new Size();
			objPort = new clsSerialPort();	
		    objds30LSettings = new clsDownloadSettings();
            objRecentFiles = new clsRecentFiles();
            
            
            //---------------------------------------------------------------------	
            // Init
            //---------------------------------------------------------------------	
            ResetSettingsToDefault();
            clsDebugTextbox.SetTextbox( this.txtInfo );            
            progressBar.Visible = false;
            toolStrip1.Visible = false;			
            progressBar.Minimum = 0;
            progressBar.Maximum = 100;
            lblVersion.Text = verGUI.ToString();
            cboTermTxType.SelectedIndex = 0;
            cborTermRxType.SelectedIndex = 0;
            

            //---------------------------------------------------------------------	
			// Enum comports
            //---------------------------------------------------------------------	
			string[] ports = System.IO.Ports.SerialPort.GetPortNames();
			foreach ( string strPort in ports ) {
				cboCOMPort.Items.Add( strPort );
			}
			
			// If no comports were found, add a few default
			if ( cboCOMPort.Items.Count == 0 ) {
				for ( int iIter = 1; iIter <= 4; iIter++ ) {
					cboCOMPort.Items.Add( "COM" + iIter.ToString() );
				}
			}
			if ( cboCOMPort.Items.Count > 0 ) {
				cboCOMPort.SelectedIndex = 0;
			} else {
				cboCOMPort.Text = "COM1";
			}
			
			cboBaudrate.SelectedIndex = 0;
            cboResetBaudrate.SelectedIndex = 0;
            cboTermBaudrate.SelectedIndex = 0;
			

            //---------------------------------------------------------------------	
			// Add device families to combobox
            //---------------------------------------------------------------------	
			clsDevices.Init();
            Hashtable htDeviceFamilys = clsDevices.DeviceFamiliesGet();
			foreach ( clsDeviceFamily objDeviceFamily in htDeviceFamilys.Values ) {
				cboFamily.Items.Add( objDeviceFamily.name );
			}
			
			//
			if ( cboFamily.Items.Count > 0 ) cboFamily.SelectedIndex = 0;
			
            
            //---------------------------------------------------------------------	
            // Load setttings
			//---------------------------------------------------------------------	
            string strPath = Application.StartupPath;
			string strSettingsFilename = strPath + "\\settings.xml";  
            string strPathRecentFiles = strPath;
            LoadSettings( strSettingsFilename );		
	        objRecentFiles.SetComboBox( cboFiles );
            objRecentFiles.LoadFiles( strPath );


            //---------------------------------------------------------------------	
            // 
			//---------------------------------------------------------------------	            
            clsds30Loader.Downloading += new clsds30Loader.DownloadingDelegate( ds30L_Downloading );


            //---------------------------------------------------------------------	
            // Startup finished
            //---------------------------------------------------------------------	
			bStartup = false;
		}//Constructor		
	
				
        //---------------------------------------------------------------------
		// Abort()
		// Description:
		//---------------------------------------------------------------------
		public void Abort()		
        {
            clsds30Loader.Abort();
        }//Abort()
	
				
        //---------------------------------------------------------------------
		// CheckLatestVersion()
		//---------------------------------------------------------------------
		public void CheckLatestVersion()		
        {
            //
            clsLatestVersionInfo objLatestVersionInfo = new clsLatestVersionInfo();
            if ( objLatestVersionInfo.CheckLatestVersion() == false ) return;

            //
            string strMsgBoxTitle = "Check for latest version";


            //-----------------------------------------------------------------
            // New version?
            //-----------------------------------------------------------------   
            if ( new Version(clsds30Loader.strVersion) < objLatestVersionInfo.lvds30Loader || verGUI < objLatestVersionInfo.lvds30LoaderGUI ) {  
                // Message
                string strMessage = string.Empty;
                if ( objLatestVersionInfo.latestVersionInfo != string.Empty ) {
                    strMessage = "Info: " + objLatestVersionInfo.latestVersionInfo + Environment.NewLine;
                }


                //-------------------------------------------------------------
                // Update or download is not allowed
                //-------------------------------------------------------------
                if ( objLatestVersionInfo.allowUpdate == false && objLatestVersionInfo.allowDownload == false ) {
                    string strQuestion = 
                        "A new version is available" + Environment.NewLine + 
                        strMessage + Environment.NewLine +
                        "Do you want to visit the homepage?"
                    ;  
                    DialogResult dgrDownload = MessageBox.Show( strQuestion, strMsgBoxTitle, MessageBoxButtons.YesNo, MessageBoxIcon.Question );
                    if ( dgrDownload == DialogResult.Yes ) {  
                        frmDS30Loader.VisitHomepage();
                    }   
             

                //-------------------------------------------------------------
                // Download allowed
                //-------------------------------------------------------------
                } else if ( objLatestVersionInfo.allowDownload == true ) {
                    string strQuestion = 
                        "A new version is available" + Environment.NewLine + 
                        strMessage + Environment.NewLine +
                        "Do you want to download the new package?"
                        
                    ;  
                    DialogResult dgrDownload = MessageBox.Show( strQuestion, strMsgBoxTitle, MessageBoxButtons.YesNo, MessageBoxIcon.Question );               
                    if ( dgrDownload == DialogResult.Yes ) {  
                         DownloadLatestPackage( objLatestVersionInfo ); 
                    } 
                

                //-------------------------------------------------------------
                // Auto update allowed
                //-------------------------------------------------------------
                } else if ( objLatestVersionInfo.allowUpdate == true ) {
                    string strQuestion = 
                        "A new version is available" + Environment.NewLine + 
                        strMessage + Environment.NewLine +
                        "Do you want to update to the new version?"
                    ;  
                    DialogResult dgrAutoUpdate = MessageBox.Show( strQuestion, strMsgBoxTitle, MessageBoxButtons.YesNo, MessageBoxIcon.Question, MessageBoxDefaultButton.Button2 );
                    
                    if ( dgrAutoUpdate == DialogResult.Yes ) { 
                        UpdateGUI( objLatestVersionInfo );
                    }  
                }
            }
        }// CheckLatestVersion()


        //---------------------------------------------------------------------
		// DownloadLatestPackage()
		// Description:
		//---------------------------------------------------------------------
		static public void DownloadLatestPackage( clsLatestVersionInfo objLatestVersionInfo )
		{	
            System.Diagnostics.Process.Start( objLatestVersionInfo.urlLatestPackage );
        }// DownloadLatestPackage()


		//---------------------------------------------------------------------
		// CheckForBL()
		// Description:
		//---------------------------------------------------------------------
		private void CheckForBL()
		{	
            clsDevice objDevice = (clsDevice)cboDevice.SelectedItem;

			if ( objDevice != null ) {
				clsDebugTextbox.ClearTextbox();
				txtInfo.Focus();				
				objPort.Setup( cboCOMPort.Text, int.Parse(cboBaudrate.Text) );
                DisableDownload();

                SetupDS30LSettings();
				bool bFindLoaderResult = false;
                Version verFw = null;
                clsds30Loader.FindLoader( objDevice, objPort, objds30LSettings, ref verFw, 0, ref bFindLoaderResult );
                
				objPort.Close();
                progressBar.Visible = false;
                EnableDownload();
			}
        }//CheckForBL()


		//---------------------------------------------------------------------
		// DisableDownload()
		// Description:
		//---------------------------------------------------------------------
		private void DisableDownload()
		{			
            btnCheck.Enabled = false;
            mnuCmdCheckForBl.Enabled = false;
            
            btnDownload.Enabled = false;
            btnDownload2.Enabled = false;
            mnuCmdDownload.Enabled = false;            

            btnAbort.Enabled = true;            
            mnuCmdAbort.Enabled = true;

            tabControl1.Enabled = false;
        }//DisableDownload()


		//---------------------------------------------------------------------
		// Download()
		// Description:
		//---------------------------------------------------------------------
		private void Download()
		{			
            //-----------------------------------------------------------------
            // Nothing to do?
            //-----------------------------------------------------------------
			if ( chkWriteProgram.Checked == false && chkWriteEEPROM.Checked == false && chkWriteConfigs.Checked == false  ) {
				MessageBox.Show( "Nothing to do.", "Download", MessageBoxButtons.OK, MessageBoxIcon.Information );
				return;
			}


            //-----------------------------------------------------------------
            // Nonexisting file?
            //-----------------------------------------------------------------
            if ( File.Exists(cboFiles.Text) == false || cboFiles.Text.Trim().Equals(string.Empty) == true ) {
                clsDebugTextbox.OutputError( "Hex-file does not exists.", 0 );
                return;
            }
		

            //-----------------------------------------------------------------
			// Find device
            //-----------------------------------------------------------------
			clsDevice objDevice = (clsDevice)cboDevice.SelectedItem;
			if ( objDevice == null ) {
                return;
            }

            
            //-----------------------------------------------------------------
            //
            //-----------------------------------------------------------------
            clsDebugTextbox.ClearTextbox();
			objPort.ResetCounters();
			txtInfo.Focus();			
            DisableDownload();
            
            
            //-----------------------------------------------------------------
            // Setup settings object and port
            //-----------------------------------------------------------------            
            SetupDS30LSettings();
            objPort.Setup( cboCOMPort.Text, int.Parse(cboBaudrate.Text) );			
            
            
            //-----------------------------------------------------------------
            // Increase process priority if polltime is low
            //-----------------------------------------------------------------
            if ( objds30LSettings.polltime < 100 ) {
                try {
                    System.Diagnostics.Process.GetCurrentProcess().PriorityClass = System.Diagnostics.ProcessPriorityClass.AboveNormal;
                } catch {
                    clsDebugTextbox.OutputInfo( "Setting proccess priority failed." );
                }
            }

  
            //-----------------------------------------------------------------
            // Download
            //-----------------------------------------------------------------
            int iStartTime = Environment.TickCount;
            bool bDownloadResult = false;
            clsds30Loader.Download( objDevice, objPort, objHex, objds30LSettings, 0, ref bDownloadResult );
            int iEndTime = Environment.TickCount;


            //-----------------------------------------------------------------
            // Restore process priority
            //-----------------------------------------------------------------
            if ( objds30LSettings.polltime < 100 ) {
                try {
                    System.Diagnostics.Process.GetCurrentProcess().PriorityClass = System.Diagnostics.ProcessPriorityClass.Normal;
                } catch {
                    clsDebugTextbox.OutputInfo( "Setting proccess priority failed." );
                }
            }


            //-----------------------------------------------------------------
            // Download finished
            //-----------------------------------------------------------------                                    
            progressBar.Visible = false;
            EnableDownload();


            //-----------------------------------------------------------------
            // Output some info
            //-----------------------------------------------------------------     
            clsDebugTextbox.OutputInfo( 
                "Tx " + objPort.bytesSentStr + " / " + 
                "Rx " + objPort.bytesReceivedStr + " / " + 
                String.Format( "{0:0.#}", Convert.ToSingle(iEndTime - iStartTime) / 1000.0 ) + "s"
                , 1 
            );


            //-----------------------------------------------------------------
            // Open terminal?
            //-----------------------------------------------------------------            
            if ( chkTermSwitchTo.Checked == true && bDownloadResult == true ) {
                btnTermOpen_Click( null, null );
                tabControl1.SelectedTab = tabTerminal;
            }
        }//Download()


		//---------------------------------------------------------------------
		// EnableDownload()
		// Description:
		//---------------------------------------------------------------------
		private void EnableDownload()
		{			
            btnCheck.Enabled = true;
			mnuCmdCheckForBl.Enabled = true;

            btnDownload.Enabled = true;
            btnDownload2.Enabled = true;
            mnuCmdDownload.Enabled = true;            
            
            btnAbort.Enabled = false;
            mnuCmdAbort.Enabled = false;
            
            tabControl1.Enabled = true;
        }//EnableDownload()


 		//---------------------------------------------------------------------
		// ds30L_Downloading()
		//---------------------------------------------------------------------
        private void ds30L_Downloading( object obj, clsDownloadingEventArgs e ) 
        {
	        if ( e.eventType == clsDownloadingEventArgs.EventType.started ) {
                clsDebugTextbox.OutputInfo( e.message, e.tabLevel );
            
            } else if ( e.eventType == clsDownloadingEventArgs.EventType.error ) {
                clsDebugTextbox.OutputError( e.message, e.tabLevel );

            } else if ( e.eventType == clsDownloadingEventArgs.EventType.warning ) {
                clsDebugTextbox.OutputWarning( e.message, e.tabLevel );
            
            } else if ( e.eventType == clsDownloadingEventArgs.EventType.info ) {
                clsDebugTextbox.OutputInfo( e.message, e.tabLevel );

            } else if ( e.eventType == clsDownloadingEventArgs.EventType.success ) {
                clsDebugTextbox.OutputSuccess( e.message, e.tabLevel );

            } else if ( e.eventType == clsDownloadingEventArgs.EventType.progressStarted ) {
                progressBar.Value = e.tabLevel;
                progressBar.Visible = true;
            
            } else if ( e.eventType == clsDownloadingEventArgs.EventType.progress ) {
                progressBar.Value = e.tabLevel;
            
            } else if ( e.eventType == clsDownloadingEventArgs.EventType.progressEnded ) {
                progressBar.Value = 0;
                progressBar.Visible = false;            

            } else if ( e.eventType == clsDownloadingEventArgs.EventType.completed ) {
                clsDebugTextbox.OutputSuccess( e.message, e.tabLevel );
            }            
        }//ds30L_Downloading()	


		//---------------------------------------------------------------------
		// Hex_Parse()
		//---------------------------------------------------------------------
		private void Hex_Parse( object obj, clsHexFileParseEventArgs e ) 
        { 
            clsHex objHex = (clsHex)obj;

			if ( e.eventType == clsHexFileParseEventArgs.EventType.started ) {
                clsDebugTextbox.OutputInfo( "Parsing hex-file...", e.tabLevel );

            } else if ( e.eventType == clsHexFileParseEventArgs.EventType.warning ) {
                clsDebugTextbox.OutputWarning( e.message, e.tabLevel );
            
            } else if ( e.eventType == clsHexFileParseEventArgs.EventType.info ) {
                clsDebugTextbox.OutputInfo( e.message, e.tabLevel );
            
            } else if ( e.eventType == clsHexFileParseEventArgs.EventType.failed ) {
                clsDebugTextbox.OutputError( "Parsing of hex-file failed", e.tabLevel );                

            } else if ( e.eventType == clsHexFileParseEventArgs.EventType.success ) {
                clsDebugTextbox.OutputSuccess( "Hex-file successfully parsed", e.tabLevel );
                clsDebugTextbox.OutputInfo( "", 0 );
                clsDebugTextbox.OutputInfo( objHex.progWordsUsed.ToString() + " program words found in " + objHex.progRowsUsed.ToString() + " rows ", e.tabLevel );
                clsDebugTextbox.OutputInfo( objHex.eeWordsUsed.ToString() + " eeprom words found ", e.tabLevel);
                clsDebugTextbox.OutputInfo( objHex.configWordsUsed.ToString() + " config words found ", e.tabLevel );			
                
            }            
		}//Hex_Parse()	


        //---------------------------------------------------------------------
		// Hex_Validate()
		//---------------------------------------------------------------------
		private void Hex_Validate( object obj, clsHexFileValidateEventArgs e ) 
        {
			if ( e.eventType == clsHexFileValidateEventArgs.EventType.started ) {
                clsDebugTextbox.OutputInfo( "Validating hex-file...", e.tabLevel );
            
            } else if ( e.eventType == clsHexFileValidateEventArgs.EventType.failed ) {
                clsDebugTextbox.OutputError( e.message );

            } else if ( e.eventType == clsHexFileValidateEventArgs.EventType.success ) {
                clsDebugTextbox.OutputSuccess( "ok" );
               
            }
		}//Hex_Validate()	


		//---------------------------------------------------------------------
		// DoParse()
		// Description:
		//---------------------------------------------------------------------
		public void DoParse()
		{	            	        
            // Check file existence
            if ( File.Exists(cboFiles.Text) == false ) {
                return;
            }

            // Get device
            clsDevice objDevice = (clsDevice)cboDevice.SelectedItem;
            if ( objDevice == null ) {
                return;
            }
            
            int iBlSizeR = 0;
            int iBlPlacementP = 0;
            

            // Here we only assume a bootloader size to be able to parse the hex-file            
            if ( cboFamily.Text == "PIC18F" ) {
                objHex = new clsHex18F( cboFiles.Text );
                iBlSizeR = 5 * objDevice.pageSizeR;
                iBlPlacementP = clsHex18F.iDefaultBlPlacementP;

             } else if ( cboFamily.Text == "PIC18FJ" ) {
                objHex = new clsHex18FJ( cboFiles.Text );
                iBlSizeR = clsHex18FJ.iDefaultBlSizeP;
                iBlPlacementP = clsHex18FJ.iDefaultBlPlacementP;
           
            } else if ( cboFamily.Text == "PIC24F" ) {
                objHex = new clsHex24F( cboFiles.Text );
                iBlSizeR = clsHex24F.iDefaultBlSizeP;
                iBlPlacementP = clsHex24F.iDefaultBlPlacementP;

            } else if ( cboFamily.Text == "PIC24FJ" ) {
                objHex = new clsHex24FJ( cboFiles.Text );
                iBlSizeR = clsHex24FJ.iDefaultBlSizeP;
                iBlPlacementP = clsHex24FJ.iDefaultBlPlacementP;
            
            } else if ( cboFamily.Text == "PIC24H" ) {
                objHex = new clsHex24H( cboFiles.Text );
                iBlSizeR = clsHex24H.iDefaultBlSizeP;
                iBlPlacementP = clsHex24H.iDefaultBlPlacementP;

            } else if ( cboFamily.Text == "dsPIC30F" ) {				
				objHex = new clsHex30F( cboFiles.Text );
				iBlSizeR = clsHex30F.iDefaultBlSizeP;
			    iBlPlacementP = clsHex30F.iDefaultBlPlacementP;
			
            } else if ( cboFamily.Text == "dsPIC33FJ" ) {
				objHex = new clsHex33FJ( cboFiles.Text );				
				iBlSizeR = clsHex33FJ.iDefaultBlSizeP;
                iBlPlacementP = clsHex33FJ.iDefaultBlPlacementP;
            
            } else {
				return;
			}

            // Custom bootloader placement
            if ( chkCustomBl.Checked == true ) {
                iBlPlacementP = int.Parse(txtCustomBlPlacementP.Text);
                iBlSizeR =  int.Parse(txtCustomBlSizeP.Text);
            }


            // Enum events
            objHex.HexFileValidate += new clsHex.HexFileValidateDelegate( Hex_Validate );
            objHex.HexFileParse += new clsHex.HexFileParseDelegate( Hex_Parse );

            // Parse settings
            clsParseSettings objParseSettings = new clsParseSettings( iBlSizeR, objDevice, chkAllowBlOverwrite.Checked, chkNoGoto.Checked, iBlPlacementP );

			// Clear info textbox
            txtInfo.Text = "";
            
            // Do parse
            bool bParseResult = false;
			objHex.ParseHexFile( objParseSettings, 0, ref bParseResult );
			
            // Use parse result
			if ( objHex.hasValidProgram ) {
				chkWriteProgram.Enabled = true;
			} else {
				chkWriteProgram.Enabled = false;
				chkWriteProgram.Checked = false;
			}
			if ( objHex.hasValidEEPROM ) {
				chkWriteEEPROM.Enabled = true;
			} else {
				chkWriteEEPROM.Enabled = false;
				chkWriteEEPROM.Checked = false;
			}
			
			if ( objHex.hasValidConfigs ) {
				chkWriteConfigs.Enabled = true;
			} else {
				chkWriteConfigs.Enabled = false;
				chkWriteConfigs.Checked = false;
			}	
			
			// Redraw graphical hex representation
            picHexContent.Refresh();
		}//DoParse();


        //-------------------------------------------------------------------------
        // HostIsWindows()
        // Description: 
        //-------------------------------------------------------------------------
        public bool HostIsWindows() 
        {
            return 
                Environment.OSVersion.Platform == PlatformID.Win32NT || 
                Environment.OSVersion.Platform == PlatformID.Win32S || 
                Environment.OSVersion.Platform == PlatformID.Win32Windows || 
                Environment.OSVersion.Platform == PlatformID.WinCE
            ;
        }// HostIsWindows()


		//-------------------------------------------------------------------------
        // LoadSettings()
        // Description: 
        //-------------------------------------------------------------------------
        public bool LoadSettings( string pstrFilename ) 
        {
			//-----------------------------------------------------------------
			// Filename
			//-----------------------------------------------------------------
			if ( File.Exists(pstrFilename) == false ) {
                objSettings = new clsSettings();
				return false;
			}

            
            clsDebugTextbox.OutputInfo( "Loading settings...", 0 );


			//-----------------------------------------------------------------
			// Deserialize
			//-----------------------------------------------------------------            
            XmlSerializer xmlSerializer = new XmlSerializer( typeof( clsSettings ) );
            TextReader textReader = new StreamReader( pstrFilename );
            try {
                objSettings = (clsSettings)xmlSerializer.Deserialize( textReader );
            } catch {
                clsDebugTextbox.OutputResult( false );
                objSettings = new clsSettings();
                textReader.Close();
                return false;
            }
            textReader.Close();


			//-----------------------------------------------------------------
			// Apply settings
			//-----------------------------------------------------------------
			
            // Options
            //mnuOptDebugmode.Checked = objSettings.Debugmode;
            mnuOptCheckVerStart.Checked = objSettings.CheckVerStart;
			
            // View options
			mnuViewOntop.Checked = objSettings.WindowOnTop;

			
            // Window size
			if ( objSettings.WindowWidth > 200 ) {
                this.Width = objSettings.WindowWidth;
            }
			if ( objSettings.WindowHeight > 200 ) {
                this.Height = objSettings.WindowHeight;
            }
            
            // Tab basic 
            cboFiles.Text = objSettings.Filename;


			//-----------------------------------------------------------------
			// Finished
			//-----------------------------------------------------------------
            clsDebugTextbox.OutputResult( true );
            return true;
		}//LoadSettings()  


		//-------------------------------------------------------------------------
		// OpenFile()
		//-------------------------------------------------------------------------
		public void OpenFile( string pstrFilename )
		{
            if ( File.Exists(pstrFilename) == false ) {
                return;
            }


            // ----------------------------------------------------------------
            // Manage recent file list
            // ----------------------------------------------------------------
            clsRecentFile objRecentFile = null;
            bool bExistingRecentFile = false;
            objRecentFiles.AddFile( pstrFilename, ref objRecentFile, ref bExistingRecentFile );
            

            // ----------------------------------------------------------------
            // If the file isn't a recent file, copy settings from gui
            // ----------------------------------------------------------------
            if ( bExistingRecentFile == false ) {
                UpdateRecentFile( objRecentFile );
            

            // ----------------------------------------------------------------
            // It's a recent file, apply settings
            // ----------------------------------------------------------------
            } else {
                // View
                mnuViewAdvanced.Checked = objRecentFile.advancedMode;

                
                // Tab basic 
			    cboCOMPort.Text = objRecentFile.Portname;
			    cboBaudrate.Text = objRecentFile.Baudrate;
			    cboFamily.Text = objRecentFile.Familyname;
                cboDevice.SelectedItem = clsDevices.DeviceGet( cboFamily.Text + objRecentFile.Devicename );
                
                // Write options
			    chkWriteProgram.Checked = objRecentFile.WriteProgram;
			    chkWriteEEPROM.Checked = objRecentFile.WriteEEPROM;
			    chkWriteConfigs.Checked = objRecentFile.WriteConfigs;
			    chkNoGoto.Checked = objRecentFile.NoGoto;
                chkCustomBl.Checked = objRecentFile.customBl;
                txtCustomBlPlacementP.Text = objRecentFile.customBlPlacementP.ToString();
                txtCustomBlSizeP.Text = objRecentFile.customBlSizeP.ToString();

                // Tab advanced
                chkWriteConfigs.Checked = objRecentFile.WriteConfigs;
			    chkNoGoto.Checked = objRecentFile.NoGoto;             
                chkAllowBlOverwrite.Checked = objRecentFile.ignoreBLOverwrite;


                // Tab timing
                txtPolltime.Text = objRecentFile.Polltime;
                txtTimeout.Text = objRecentFile.Timeout;

                // Tab rest
                rdbResetCommand.Checked = objRecentFile.CommandReset;
                txtResetCommand.Text = objRecentFile.ResetCommand;
                cboResetBaudrate.Text = objRecentFile.resetBaudrate;
                rdbResetDtr.Checked = objRecentFile.DTRReset;
                rdbResetManual.Checked = objRecentFile.ManualReset;
                rdbResetRts.Checked = objRecentFile.RTSReset;
                txtResettime.Text = objRecentFile.ResetTime.ToString();

                // Tab device activation
                rdbActivateDTR.Checked = objRecentFile.ActivateDTR;
                rdActivatebRTS.Checked = objRecentFile.ActivateRTS;

                // Tab terminal
                cboTermBaudrate.Text = objRecentFile.termBaudrate;
                chkTermSwitchTo.Checked = objRecentFile.termSwithTo;
                cborTermRxType.SelectedIndex = objRecentFile.termRxType;
                cboTermTxType.SelectedIndex = objRecentFile.termTxType;
                txtTermTx.Text = objRecentFile.termTx;
            }

            // ----------------------------------------------------------------
            // Do actual opening of the hex-file
            // ----------------------------------------------------------------
            DoParse();
		}// OpenFile()
	

		//-------------------------------------------------------------------------
		// ResetSettingsToDefault()
		//-------------------------------------------------------------------------
		public void ResetSettingsToDefault()
		{
            //
            mnuOptDebugmode.Checked = false;
            mnuViewAdvanced.Checked = false;

            // tab basic settings
            chkWriteProgram.Checked = false;
            chkWriteEEPROM.Checked = false;

            // Tab advanced
            chkWriteConfigs.Checked = false;
            chkNoGoto.Checked = false;
            chkAllowBlOverwrite.Checked = false;
            chkCustomBl.Checked = false;
            txtCustomBlPlacementP.Text = "1";
            txtCustomBlSizeP.Text = "1";

            // tab timing
            txtTimeout.Text = "5000";
            txtPolltime.Text = "250";

            // tab device reset
            rdbResetManual.Checked = true;
            txtResettime.Text = "250";
            txtResetCommand.Text = "a;0;ff;e0";

            // tab device activation
            rdbActivateNone.Checked = true;

            // Tab terminal
            chkTermSwitchTo.Checked = false;
		}// ResetSettingsToDefault()

	
		//-------------------------------------------------------------------------
		// SaveSettings()
		// Description: 
		//-------------------------------------------------------------------------
		public void SaveSettings()
		{	
            string strPath = Application.StartupPath;
            
            
            //-----------------------------------------------------------------
			// Recent filens
            //-----------------------------------------------------------------
            UpdateRecentFile( cboFiles.Text );
            objRecentFiles.SaveFiles( strPath );


            //-----------------------------------------------------------------
			// Filename
            //-----------------------------------------------------------------			
			string strFilename = strPath + "\\settings.xml";

            
            //-----------------------------------------------------------------
            //
            //-----------------------------------------------------------------

			// Options
			objSettings.Debugmode = mnuOptDebugmode.Checked;
            objSettings.CheckVerStart = mnuOptCheckVerStart.Checked;

            // View options
			objSettings.WindowOnTop = mnuViewOntop.Checked;

			
            // Window size
			objSettings.WindowWidth = this.Width;
            if ( btnShowOutput.Checked == false ) {
			    objSettings.WindowHeight = this.Height;
            } else {
                objSettings.WindowHeight = this.Height;
            }
			
            // Tab basic settings
            objSettings.Filename = cboFiles.Text;
 
            
            //-----------------------------------------------------------------
            // Serialize
            //-----------------------------------------------------------------           
            XmlSerializer xmlSerializer = new XmlSerializer( typeof(clsSettings) );
            TextWriter textWriter = new StreamWriter( strFilename );
            xmlSerializer.Serialize( textWriter, objSettings );
            textWriter.Close();
		}//SaveSettings()         
        

        //-------------------------------------------------------------------------
		// SetPanel2CollapsedState()
		//-------------------------------------------------------------------------
        private void SetPanel2CollapsedState( bool pbCollapsed ) {
            splitContainer1.Panel2Collapsed = pbCollapsed;

            splitContainer1.Panel2.Tag = splitContainer1.Panel2Collapsed;
            btnShowOutput.Checked = !splitContainer1.Panel2Collapsed;
            mnuViewOutput.Checked = !splitContainer1.Panel2Collapsed;
        }//SetPanel2CollapsedState
        

        //-------------------------------------------------------------------------
		// SetupDS30LSettings()
		// Description: 
		//-------------------------------------------------------------------------
		public void SetupDS30LSettings()
		{	
            // Basic
            objds30LSettings.writeProgram = chkWriteProgram.Checked;
            objds30LSettings.writeEeprom = chkWriteEEPROM.Checked;

            // Advanced
            objds30LSettings.writeConfigs = chkWriteConfigs.Checked;
            objds30LSettings.noGoto = chkNoGoto.Checked;
            objds30LSettings.allowBlOverwrite = chkAllowBlOverwrite.Checked;     
            objds30LSettings.customBlPlacementP = int.Parse( txtCustomBlPlacementP.Text );
            objds30LSettings.customBlSizeP = int.Parse( txtCustomBlSizeP.Text );
            objds30LSettings.customBl = chkCustomBl.Checked;

            // Timing
            objds30LSettings.timeout = int.Parse( txtTimeout.Text );
            objds30LSettings.polltime = int.Parse( txtPolltime.Text );   
            
            // Reset
            objds30LSettings.resetCommand = rdbResetCommand.Checked;
            objds30LSettings.resetCommandSequence = txtResetCommand.Text;
            objds30LSettings.resetBaudrate = int.Parse( cboResetBaudrate.Text );
            objds30LSettings.resetDtr = rdbResetDtr.Checked;
            objds30LSettings.resetRts = rdbResetRts.Checked;    
            objds30LSettings.resetTime = int.Parse( txtResettime.Text );

            // Activation
            objds30LSettings.activateDtr = rdbActivateDTR.Checked;
            objds30LSettings.activateRts = rdActivatebRTS.Checked;
		}//SetupDS30LSettings()  
        

        //-------------------------------------------------------------------------
		// TermUpdateButtons()
		//-------------------------------------------------------------------------       
        private void TermUpdateButtons()
        {
            //
            btnTermOpen.Enabled = !objPort.isOpen;
            btnTermClose.Enabled = objPort.isOpen;
            txtTermTx.Enabled = objPort.isOpen;
            cboTermBaudrate.Enabled = !objPort.isOpen;

            //              
            cboCOMPort.Enabled = !objPort.isOpen;
            btnCheck.Enabled = !objPort.isOpen;
            btnDownload.Enabled = !objPort.isOpen;
            mnuCmdDownload.Enabled = !objPort.isOpen;
        }// TermUpdateButtons()

 
        //---------------------------------------------------------------------
		// UpdateGUI()
		// Description:
		//---------------------------------------------------------------------
		static public bool UpdateGUI( clsLatestVersionInfo objLatestVersionInfo )
		{	
            // Download file
            try {
                WebClient Client = new WebClient ();
                Client.DownloadFile( objLatestVersionInfo.urlds30Loader_dll, "ds30 loader.dll.new");
                Client.DownloadFile( objLatestVersionInfo.urlds30LoaderGUI_exe, "ds30 loader GUI.exe.new");
            } catch {
                MessageBox.Show( "Download failed. Update aborted.", "Update", MessageBoxButtons.OK, MessageBoxIcon.Exclamation );
                return false;
            }

            // Create bat-file
            TextWriter tw = new StreamWriter("update.bat");
            tw.WriteLine( "@echo off" );
            tw.WriteLine( "echo Wait for the application to close. Then press any key to continue update." );
            tw.WriteLine( "echo Press CTRL+C to abort." );
            tw.WriteLine( "pause" );
            tw.WriteLine( "del \"ds30 loader.dll\"" );
            tw.WriteLine( "del \"ds30 loader GUI.exe\"" );
            tw.WriteLine( "ren \"ds30 loader.dll.new\" \"ds30 loader.dll\"" );
            tw.WriteLine( "ren \"ds30 loader GUI.exe.new\" \"ds30 loader GUI.exe\"" );
            tw.WriteLine( "start \"\" \"ds30 loader gui.exe\"" );
            tw.WriteLine( "del update.bat" );
            tw.Close();

            // Start bat
            try {
                System.Diagnostics.ProcessStartInfo a = new System.Diagnostics.ProcessStartInfo();
                a.WindowStyle = System.Diagnostics.ProcessWindowStyle.Normal;
                a.FileName = "update.bat";
                a.WorkingDirectory = Path.GetDirectoryName( Application.ExecutablePath );
                /*System.Diagnostics.Process objUpdateProcess = */System.Diagnostics.Process.Start( a );                    
            } catch {
                MessageBox.Show( "Update failed.", "Update", MessageBoxButtons.OK, MessageBoxIcon.Exclamation );
                return false;
            }

            // Close application
            Application.Exit();

            return true;
        }// UpdateGUI()


        //-------------------------------------------------------------------------
		// UpdateRecentFile()
		// Description: 
		//-------------------------------------------------------------------------
		public void UpdateRecentFile( string pstrFilename )
		{	
            clsRecentFile objRecentFile = objRecentFiles.GetFile( pstrFilename );
            if ( objRecentFiles != null ) {
                UpdateRecentFile( objRecentFile );
            } 
        }// UpdateRecentFile()


        //-------------------------------------------------------------------------
		// UpdateRecentFile()
		// Description: 
		//-------------------------------------------------------------------------
		public void UpdateRecentFile( clsRecentFile pobjRecentFile )
		{	
            if ( pobjRecentFile == null ) {
                return;
            }

            pobjRecentFile.advancedMode = mnuViewAdvanced.Checked;
			
            // Tab basic settings
			pobjRecentFile.Portname = cboCOMPort.Text;
			pobjRecentFile.Baudrate = cboBaudrate.Text;
			pobjRecentFile.Familyname = cboFamily.Text;
			pobjRecentFile.Devicename = cboDevice.Text;
			pobjRecentFile.WriteProgram = chkWriteProgram.Checked; 
			pobjRecentFile.WriteEEPROM = chkWriteEEPROM.Checked;

            // Tab advanced
			pobjRecentFile.WriteConfigs = chkWriteConfigs.Checked;
			pobjRecentFile.NoGoto = chkNoGoto.Checked;
            pobjRecentFile.customBl = chkCustomBl.Checked;
            pobjRecentFile.customBlPlacementP = int.Parse( txtCustomBlPlacementP.Text );
            pobjRecentFile.customBlSizeP = int.Parse( txtCustomBlSizeP.Text );

            // Tab timing
            pobjRecentFile.Polltime = txtPolltime.Text;
            pobjRecentFile.Timeout = txtTimeout.Text;

            // Tab device reset
            pobjRecentFile.CommandReset = rdbResetCommand.Checked;
            pobjRecentFile.ResetCommand = txtResetCommand.Text;
            pobjRecentFile.resetBaudrate = cboResetBaudrate.Text;

            pobjRecentFile.DTRReset = rdbResetDtr.Checked;
            pobjRecentFile.ManualReset = rdbResetManual.Checked;
            
            pobjRecentFile.RTSReset = rdbResetRts.Checked;
            pobjRecentFile.ResetTime = int.Parse( txtResettime.Text );

            // Tab device activation
            pobjRecentFile.ActivateDTR = rdbActivateDTR.Checked;
            pobjRecentFile.ActivateRTS = rdActivatebRTS.Checked;

            // Tab terminal
            pobjRecentFile.termBaudrate = cboTermBaudrate.Text;
            pobjRecentFile.termSwithTo = chkTermSwitchTo.Checked;
            pobjRecentFile.termRxType = cborTermRxType.SelectedIndex;
            pobjRecentFile.termTxType = cboTermTxType.SelectedIndex;
            pobjRecentFile.termTx = txtTermTx.Text;
		}//UpdateRecentFile()   


        //-------------------------------------------------------------------------
		// VisitHomepage()
		// Description: 
		//-------------------------------------------------------------------------
		static public void VisitHomepage()
		{	
            System.Diagnostics.Process.Start( strURLHomepage );  
		}//VisitHomepage()         		


		//---------------------------------------------------------------------
		// mnuFileExit_Click()
		//---------------------------------------------------------------------
		private void mnuFileExit_Click( object sender, EventArgs e )
		{
			Application.Exit();
		}//mnuFileExit_Click()
		
		
		//---------------------------------------------------------------------
		// cboFamily_SelectedIndexChanged()
		//---------------------------------------------------------------------
		private void cboFamily_SelectedIndexChanged( object sender, EventArgs e )
		{
			// Clear devices in combobox
			cboDevice.Items.Clear();
			
			// Get selected device family
			clsDeviceFamily objDeviceFamily = clsDevices.DeviceFamilyGet( cboFamily.Text );
			if ( objDeviceFamily == null ) return;
			
			// Populate combobox with devices
			Hashtable htDevices = objDeviceFamily.DevicesGet();			
			foreach ( clsDevice objDevice in htDevices.Values ) {
				if ( objDevice.family == objDeviceFamily ) {
                    cboDevice.Items.Add( objDevice );
				}
			}
			
			// Select the first device
			if ( cboDevice.Items.Count > 0 ) {
				cboDevice.SelectedIndex = 0;
			} else {
				cboDevice.Text = "";
			}
		}//cboFamily_SelectedIndexChanged()
		
		
		//---------------------------------------------------------------------
		// btnBrowse_Click()
		//---------------------------------------------------------------------
		private void btnBrowse_Click( object sender, EventArgs e )
		{
			OpenFileDialog  dialog = new OpenFileDialog ();
			dialog.InitialDirectory = "";
			dialog.Title = "Choose hex-file";
			dialog.Filter = strHexFileFilter;
			dialog.FilterIndex = 0;
			
			// User presses OK
			if ( dialog.ShowDialog() == DialogResult.OK ) {
                // File changed?
                if ( dialog.FileName == cboFiles.Text ) {
                    return;
                }

                // Apply settings for old file
                UpdateRecentFile( cboFiles.Text );

                // Apply new file
				cboFiles.Text = dialog.FileName;
				OpenFile( cboFiles.Text );
			 }			
		}//btnBrowse_Click()
		
		
		//---------------------------------------------------------------------
		// frmDSLoader_FormClosing()
		//---------------------------------------------------------------------
		private void frmDSLoader_FormClosing( object sender, FormClosingEventArgs e )
		{
			SaveSettings();
		}//btnCheck_Click()
		
		
		//---------------------------------------------------------------------
		// cboDevice_SelectedIndexChanged()
		//---------------------------------------------------------------------
		private void cboDevice_SelectedIndexChanged( object sender, EventArgs e )
		{
			if ( bStartup == false ) DoParse();
		}//btnCheck_Click()
		
		
		//---------------------------------------------------------------------
		// mnuEditDebugmode_CheckedChanged()
		//---------------------------------------------------------------------
        private void mnuEditDebugmode_CheckedChanged(object sender, EventArgs e)
        {
            clsds30Loader.debugMode = mnuOptDebugmode.Checked;
            if ( bStartup == false && clsds30Loader.debugMode == true ) {
                DoParse();
            }
        }//mnuEditDebugmode_CheckedChanged()
		
		
		//---------------------------------------------------------------------
		// mnuHelpCheckLatest_Click()
		//---------------------------------------------------------------------
        private void mnuHelpCheckLatest_Click(object sender, EventArgs e)
        {
            frmVersion objVersionForm = new frmVersion();
            objVersionForm.ShowDialog();
        }//mnuHelpCheckLatest_Click()
		
		
		//---------------------------------------------------------------------
		// mnuHelpVisitHomepage_Click()
		//---------------------------------------------------------------------
        private void mnuHelpVisitHomepage_Click(object sender, EventArgs e)
        {
            VisitHomepage();
        }//mnuHelpVisitHomepage_Click()
		
		
		//---------------------------------------------------------------------
		// mnuViewMicro_Click()
		//---------------------------------------------------------------------
        private void mnuViewMicro_Click(object sender, EventArgs e)
        {
            sizeBeforeMicro.Width = this.Width;
            sizeBeforeMicro.Height = this.Height;

            this.Width = 170;
            this.Height = toolStrip1.Height;
            this.FormBorderStyle = FormBorderStyle.None;
            this.ShowInTaskbar = false;

            mnuViewMicro.Enabled = false;
            menuStrip1.Visible = false;             
            tabControl1.Visible = false;
            txtInfo.Visible = false;
            toolStrip2.Visible = false;
            statusStrip1.Visible = false;
            this.ControlBox = false;
            this.Text = "";

            toolStrip1.Top = menuStrip1.Top;
            toolStrip1.Visible = true;            
            
            //progressBar.Top = toolStrip1.Top + (toolStripButton1.Height - progressBar.Height)/2;
            //progressBar.Left = toolStripButton1.Width + toolStripButton2.Width + 20;
            //progressBar.Width = this.Width - progressBar.Left - 35;            
            
            progressBar.Left = toolStrip1.Left + 10;
            progressBar.Top = toolStrip1.Top + toolStrip1.Height;
            progressBar.Width = toolStrip1.Width - 20;

            if ( mnuViewOntop.Checked == false  ) {
                mnuViewOntop.Checked = true;
            }
        }//mnuViewMicro_Click()
		
		
		//---------------------------------------------------------------------
		// toolStripButton1_Click()
		//---------------------------------------------------------------------
        private void toolStripButton1_Click(object sender, EventArgs e)
        {
            mnuViewMicro.Enabled = true;
            toolStrip1.Visible = false;
            menuStrip1.Visible = true;
            tabControl1.Visible = true;
            txtInfo.Visible = true;
            toolStrip2.Visible = true;
            statusStrip1.Visible = true;
            this.ControlBox = true;
            this.Text = "ds30 Loader";

            this.Width = sizeBeforeMicro.Width;
            this.Height = sizeBeforeMicro.Height;
            this.FormBorderStyle = FormBorderStyle.Sizable;
            this.ShowInTaskbar = true;

            progressBar.Top = 7;
            progressBar.Left = 253;
            progressBar.Width = tabControl1.Width + tabControl1.Left - progressBar.Left;

        }//toolStripButton1_Click()
		
		
		//---------------------------------------------------------------------
		// frmDSLoader_MouseDown()
		//---------------------------------------------------------------------
        private void frmDSLoader_MouseDown(object sender, MouseEventArgs e)
        {
            if ( HostIsWindows() == true ) {
                if ( e.Button == MouseButtons.Left ) {
                    ReleaseCapture();
                    SendMessage( Handle, WM_NCLBUTTONDOWN, HT_CAPTION, 0 );
                }
            }
        }//frmDSLoader_MouseDown()
		
		
		//---------------------------------------------------------------------
		// toolStrip1_MouseDown()
		//---------------------------------------------------------------------
        private void toolStrip1_MouseDown(object sender, MouseEventArgs e)
        {
           if ( e.Button == MouseButtons.Left ) {
                ReleaseCapture();
                SendMessage( Handle, WM_NCLBUTTONDOWN, HT_CAPTION, 0 );
            }
        }//toolStrip1_MouseDown()
		
		
		//---------------------------------------------------------------------
		// btnDownload2_Click()
		//---------------------------------------------------------------------
        private void btnDownload2_Click(object sender, EventArgs e)
        {
            Download();
        }//btnDownload2_Click()
		
		
		//---------------------------------------------------------------------
		// txtInfo_TextChanged()
		//---------------------------------------------------------------------
        private void txtInfo_TextChanged(object sender, EventArgs e)
        {
            if ( mnuViewMicro.Checked == true ) {
                btnDownload2.ToolTipText = txtInfo.Text;
            }

            if ( btnShowOutput.Checked == false ) {
                btnShowOutput.ToolTipText = txtInfo.Text;
            }
        }//txtInfo_TextChanged()
		
		
		//---------------------------------------------------------------------
		// mnuViewOntop_CheckedChanged()
		//---------------------------------------------------------------------
        private void mnuViewOntop_CheckedChanged(object sender, EventArgs e)
        {
            this.TopMost = mnuViewOntop.Checked;
        }//mnuViewOntop_CheckedChanged()
		
		
		//---------------------------------------------------------------------
		// mnuCmdDownload_Click()
		//---------------------------------------------------------------------
        private void mnuCmdDownload_Click(object sender, EventArgs e)
        {
            Download();
        }//mnuViewOntop_CheckedChanged()
		
		
		//---------------------------------------------------------------------
		// mnuCmdAbort_Click()
		//---------------------------------------------------------------------
        private void mnuCmdAbort_Click(object sender, EventArgs e)
        {
            Abort();
        }//mnuCmdAbort_Click()
		
		
		//---------------------------------------------------------------------
		// frmDSLoader_Shown()
		//---------------------------------------------------------------------
        private void frmDSLoader_Shown(object sender, EventArgs e)
        {
            // Check for new version?
            if ( mnuOptCheckVerStart.Checked == true ) {
                CheckLatestVersion();
            }

            // Open last file
            OpenFile( cboFiles.Text );
        }//frmDSLoader_Shown()
		
		
		//---------------------------------------------------------------------
		// mnuHelpAbout_Click()
		//---------------------------------------------------------------------
        private void mnuHelpAbout_Click(object sender, EventArgs e)
        {
            frmAbout objAbout = new frmAbout();
            objAbout.ShowDialog( this );
        }//mnuHelpAbout_Click()
		
		
		//---------------------------------------------------------------------
		// mnuHelpDocAPI_Click()
		//---------------------------------------------------------------------
        private void mnuHelpDocAPI_Click(object sender, EventArgs e)
        {
            try {
                System.Diagnostics.Process.Start( Path.GetDirectoryName(Application.ExecutablePath) + @"\docs\ds30 loader - api.pdf" );
            } catch ( Exception ex ) {
                MessageBox.Show( ex.Message, "", MessageBoxButtons.OK, MessageBoxIcon.Information  );
            }
        }//mnuHelpDocAPI_Click()
		
		
		//---------------------------------------------------------------------
		// chkNoGoto_CheckedChanged()
		//---------------------------------------------------------------------
        private void chkNoGoto_CheckedChanged(object sender, EventArgs e)
        {
            if ( bStartup == false ) {
                DoParse();
            }
        }//chkNoGoto_CheckedChanged()
		
		
		//---------------------------------------------------------------------
		// btnDownload_Click()
		//---------------------------------------------------------------------
        private void btnDownload_Click(object sender, EventArgs e)
        {
            Download();
        }//btnDownload_Click()
		
		
		//---------------------------------------------------------------------
		// btnCheck_Click()
		//---------------------------------------------------------------------
        private void btnCheck_Click(object sender, EventArgs e)
        {
            CheckForBL();
        }//btnCheck_Click()
		
		
		//---------------------------------------------------------------------
		// btnAbort_Click()
		//---------------------------------------------------------------------
        private void btnAbort_Click(object sender, EventArgs e)
        {
            Abort();
        }//btnAbort_Click()
		
		
		//---------------------------------------------------------------------
		// btnShowOutput_CheckedChanged()
		//---------------------------------------------------------------------
        private void btnShowOutput_CheckedChanged(object sender, EventArgs e)
        {
            SetPanel2CollapsedState( !btnShowOutput.Checked );
        }//btnShowOutput_CheckedChanged()
		
		
		//---------------------------------------------------------------------
		// frmDS30Loader_Activated()
        // Description: reload hex-file when windows is actived, maybe the user
        //              is returning from mplab...
		//---------------------------------------------------------------------
        private void frmDS30Loader_Activated(object sender, EventArgs e)
        {
            if ( bStartup == true ) {
                return;
            }

            if ( objHex != null ) {
                if ( File.Exists(cboFiles.Text) ) {
                    if ( objHex.objParsedSettings.fileTimestamp != File.GetLastWriteTime(cboFiles.Text) ) {
                        DoParse();
                    }
                }
            }        
        }//frmDS30Loader_Activated()
		
		
		//---------------------------------------------------------------------
		// rdbCommandReset_CheckedChanged()
		//---------------------------------------------------------------------
        private void rdbCommandReset_CheckedChanged(object sender, EventArgs e)
        {
            txtResetCommand.Enabled = rdbResetCommand.Checked;        
            cboResetBaudrate.Enabled = rdbResetCommand.Checked;
        }//rdbCommandReset_CheckedChanged()
		
		
		//---------------------------------------------------------------------
		// txtResetCommand_TextChanged()
		//---------------------------------------------------------------------
        private void txtResetCommand_TextChanged(object sender, EventArgs e)
        {
            bool bSplitResult = false;
            objPort.SplitHexStringToBytes( txtResetCommand.Text, ref bSplitResult );
            if ( bSplitResult == false ) {
                lblIncorrectFormat.Visible = true;
                return;
            }

            lblIncorrectFormat.Visible = false;
        }//txtResetCommand_TextChanged()
		
		
		//---------------------------------------------------------------------
		// tabControl1_SelectedIndexChanged()
		//---------------------------------------------------------------------
        private void tabControl1_SelectedIndexChanged(object sender, EventArgs e)
        {
            if ( tabControl1.SelectedIndex == 4 ) {
                btnTermClose.Enabled = objPort.isOpen;
                btnTermOpen.Enabled = !objPort.isOpen;
            }
        }// tabControl1_SelectedIndexChanged()
		

		//---------------------------------------------------------------------
		// splitContainer1_Panel1_Paint()
		//---------------------------------------------------------------------
        private void splitContainer1_Panel1_Paint(object sender, PaintEventArgs e)
        {
            //tabControl1.Refresh();            
            tabControl1.SelectedTab.Refresh();
        }// splitContainer1_Panel1_Paint()
		
		
		//---------------------------------------------------------------------
		// btnTermOpen_Click()
		//---------------------------------------------------------------------
        private void btnTermOpen_Click(object sender, EventArgs e)
        {
            // Configure port
            objPort.Setup( cboCOMPort.Text, int.Parse(cboTermBaudrate.Text) );
            objPort.dtrEnable = rdbActivateDTR.Checked;
            objPort.rtsEnable = rdActivatebRTS.Checked;            
            //objPort.objPort.Encoding = System.Text.Encoding.Default;

            // 
            objPort.objPort.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(objPort_DataReceived);
            
            // Empty buffers and open port
            objPort.EmptyBuffers( true, true );
            objPort.Open();
            if ( objPort.isOpen == false ) {
                clsDebugTextbox.OutputError( "Terminal: could not open port", 0 );
            }

            TermUpdateButtons();
        }// btnTermOpen_Click()
		
		
		//---------------------------------------------------------------------
		// objPort_DataReceived()
		//---------------------------------------------------------------------
        void objPort_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            System.IO.Ports.SerialPort pobjPort = (System.IO.Ports.SerialPort)sender;

            // Text
            if ( cborTermRxType.SelectedItem.ToString() == "Text" ) {
                
                txtTermRx.AppendText( pobjPort.ReadExisting() + Environment.NewLine );
            
            // Values
            } else {
                //
                string strRxType = cborTermRxType.SelectedItem.ToString().ToLower();

                // Get wordsize
                int iWordSizeBytes;
                if ( strRxType.StartsWith("8") == true ) {
                    iWordSizeBytes = 1;
                } else if ( strRxType.StartsWith("16") == true ) {
                    iWordSizeBytes = 2;
                } else if ( strRxType.StartsWith("32") == true ) {
                    iWordSizeBytes = 4;
                } else {
                    return;
                }

                // Nr of words available
                int iBytesAvailable = pobjPort.BytesToRead;                
                int iWords = (int)Math.Floor( (decimal)(iBytesAvailable / (int)iWordSizeBytes) );

                // Read words
                byte[] bRxBytes = new byte[iWords*iWordSizeBytes];                
                pobjPort.Read( bRxBytes, 0, iWords*iWordSizeBytes );

                // Calculate value and output
                bool bHex = strRxType.Contains( "hex" );
                bool bUnsigned = strRxType.Contains( "unsigned" );
                string strFormat = "X" + (iWordSizeBytes*2).ToString();

                int iValue = 0;
                for ( int iWord = 0; iWord < iWords; iWord++ ) {
                    // Calculate
                    iValue = 0;
                    for ( int iByte = 0; iByte < iWordSizeBytes; iByte++ ) {
                        iValue += bRxBytes[ iWord * iWordSizeBytes + iByte] << ( 8 * (iWordSizeBytes - iByte - 1) );
                    }                    
                    
                    // Output
                    if ( bHex == true ) {
                        txtTermRx.AppendText( "0x" + iValue.ToString(strFormat) + " " );
                    } else if ( bUnsigned == true ) {
                        txtTermRx.AppendText( iValue.ToString() + " " );
                    }
                }                
            }
        }// objPort_DataReceived()
		
		
		//---------------------------------------------------------------------
		// btnTermClose_Click()
		//---------------------------------------------------------------------
        private void btnTermClose_Click(object sender, EventArgs e)
        {
            objPort.Close();
            objPort.objPort.DataReceived -= new System.IO.Ports.SerialDataReceivedEventHandler(objPort_DataReceived);
            TermUpdateButtons();
        }// btnTermClose_Click()
		
		
		//---------------------------------------------------------------------
		// mnuOptResetSettings_Click()
		//---------------------------------------------------------------------
        private void mnuOptResetSettings_Click(object sender, EventArgs e)
        {
            ResetSettingsToDefault();
        }// mnuOptResetSettings_Click()
		
		
		//---------------------------------------------------------------------
		// mnuViewAdvanced_CheckedChanged()
		//---------------------------------------------------------------------
        private void mnuViewAdvanced_CheckedChanged(object sender, EventArgs e)
        {
            //-----------------------------------------------------------------
            // Basic
            //-----------------------------------------------------------------            
            if ( mnuViewAdvanced.Checked == false ) {
                ResetSettingsToDefault();

                // Menus
                mnuOptDebugmode.Visible = false;
                mnuViewMicro.Visible = false;

                // Toolbar
                btnCheck.Visible = false;
                btnShowOutput.Checked = true;
                btnShowOutput.Visible = false;

                // Tabcontrol
                chkNoGoto.Visible = false;
                tabControl2.TabPages.Add( tabControl1.TabPages[1] );
                tabControl2.TabPages.Add( tabControl1.TabPages[1] );
                tabControl2.TabPages.Add( tabControl1.TabPages[1] );
                tabControl2.TabPages.Add( tabControl1.TabPages[1] );
                tabControl2.TabPages.Add( tabControl1.TabPages[1] );

            
            //-----------------------------------------------------------------
            // Advanced
            //-----------------------------------------------------------------
            } else {
                // Menus
                mnuOptDebugmode.Visible = true;
                //mnuViewMicro.Visible = true;

                // Toolbar
                btnCheck.Visible = true;
                btnShowOutput.Visible = true;

                // Tabcontrol
                chkNoGoto.Visible = true;
                tabControl1.TabPages.Add( tabControl2.TabPages[0] );
                tabControl1.TabPages.Add( tabControl2.TabPages[0] );
                tabControl1.TabPages.Add( tabControl2.TabPages[0] );
                tabControl1.TabPages.Add( tabControl2.TabPages[0] );
                tabControl1.TabPages.Add( tabControl2.TabPages[0] );
                
            }
        }// mnuViewAdvanced_CheckedChanged()
		
		
		//---------------------------------------------------------------------
		// btnTermClearRx_Click()
		//---------------------------------------------------------------------
        private void btnTermClearRx_Click(object sender, EventArgs e)
        {            
            txtTermRx.Clear();
        }// btnTermClearRx_Click()
		
		
		//---------------------------------------------------------------------
		// rdbResetManual_CheckedChanged()
		//---------------------------------------------------------------------
        private void rdbResetManual_CheckedChanged(object sender, EventArgs e)
        {
            txtResettime.Enabled = !rdbResetManual.Checked;
        }// rdbResetManual_CheckedChanged()

        
        //---------------------------------------------------------------------
		// txtTermTxHex_KeyDown()
		//---------------------------------------------------------------------
        private void txtTermTxHex_KeyDown(object sender, KeyEventArgs e)
        {
            // Send when enter is pressed
            if ( e.KeyCode == Keys.Enter ) {
                // Text
                if ( cboTermTxType.SelectedIndex == 0 ) {
                    objPort.objPort.Write( txtTermTx.Text );
                    txtTermTx.SelectAll();

                // Hex 8bit
                } else {            
                    bool bSplitResult = false;
                    byte[] bBytes = objPort.SplitHexStringToBytes( txtTermTx.Text, ref bSplitResult );
                    if ( bSplitResult == true ) {
                        objPort.SendBytes( ref bBytes, bBytes.Length );
                        txtTermTx.SelectAll();
                    }
                }
            }
        }// txtTermTxHex_KeyDown()	
		
		
		//---------------------------------------------------------------------
		// mnuCmdCheckForBl_Click()
		//---------------------------------------------------------------------
        private void mnuCmdCheckForBl_Click(object sender, EventArgs e)
        {
            CheckForBL();
        }// mnuCmdCheckForBl_Click()
		
		
		//---------------------------------------------------------------------
		// mnuViewOutput_Click()
		//---------------------------------------------------------------------
        private void mnuViewOutput_Click(object sender, EventArgs e)
        {
            SetPanel2CollapsedState( !mnuViewOutput.Checked );
        }// mnuViewOutput_Click()
		
		
		//---------------------------------------------------------------------
		// mnuViewOutput_Click()
		//---------------------------------------------------------------------
        private void picHexContent_Paint(object sender, PaintEventArgs e)
        {
            if ( objHex == null ) {
                return;
            }
            //
            clsDevice objDevice = (clsDevice)cboDevice.SelectedItem;
            if ( objDevice == null ) {
                picHexContent.Image = null;
                return;
            }
 
            //            
            int iMaxRow = objDevice.flashSizeP / objDevice.rowsizeW / 2;
            //int iMaxPage = iMaxRow / objDevice.pageSizeR;
 
            //
            Bitmap bmpHex = new Bitmap( picHexContent.Width, iMaxRow, e.Graphics );
            Graphics grpHex = Graphics.FromImage( bmpHex );            
 
            //            
            grpHex.Clear( Color.White );
            for ( int iRow = 0; iRow < iMaxRow; iRow++ ) {
                // Bootloader & User application
                if (  objHex.bProgRowUsed[iRow] == true && iRow >= objHex.GetBootloaderStartRow(objHex.objParsedSettings) && iRow <= objHex.GetBootloaderEndRow(objHex.objParsedSettings) ) {
                    grpHex.DrawLine( Pens.Red, 0, iRow, bmpHex.Width-1, iRow );
                
                // User application
                } else if ( objHex.bProgRowUsed[iRow] == true ) {
                    grpHex.DrawLine( Pens.Green, 0, iRow, bmpHex.Width-1, iRow );
                }

                // Bootloader
                if ( iRow >= objHex.GetBootloaderStartRow(objHex.objParsedSettings) && iRow <= objHex.GetBootloaderEndRow(objHex.objParsedSettings) ) {
                    grpHex.DrawLine( Pens.Orange, 0, iRow, bmpHex.Width-1, iRow );
                
                // User application
                } else if ( objHex.bProgRowUsed[iRow] == true ) {
                    grpHex.DrawLine( Pens.Green, 0, iRow, bmpHex.Width-1, iRow );
                }
            }
 
            //
            e.Graphics.DrawImage( 
                bmpHex,
                new Rectangle(0, 0, picHexContent.Width, picHexContent.Height),
                new Rectangle(0, 0, bmpHex.Width, bmpHex.Height), 
                GraphicsUnit.Pixel                 
            );
        }// mnuViewOutput_Click()
		
		
		//---------------------------------------------------------------------
		// picHexContent_SizeChanged()
		//---------------------------------------------------------------------
        private void picHexContent_SizeChanged(object sender, EventArgs e)
        {
            picHexContent.Refresh();
        }// picHexContent_SizeChanged()
		
		
		//---------------------------------------------------------------------
		// cboFiles_SelectedIndexChanged()
		//---------------------------------------------------------------------
        private void cboFiles_SelectedIndexChanged(object sender, EventArgs e)
        {
            // Update current
            if ( objHex != null ) {
                UpdateRecentFile( objHex.filename );
            }

            OpenFile( cboFiles.Text );
        }// cboFiles_SelectedIndexChanged()
		
				
		//---------------------------------------------------------------------
		// chkCustomBl_CheckedChanged()
		//---------------------------------------------------------------------
        private void chkCustomBl_CheckedChanged(object sender, EventArgs e)
        {
            txtCustomBlPlacementP.Enabled = chkCustomBl.Checked;
            txtCustomBlSizeP.Enabled = chkCustomBl.Checked;

            if ( chkCustomBl.Checked == true ) {
                txtCustomBlPlacementP.Focus();
            }

            if ( bStartup == false ) {
                DoParse();
            }
        }// chkCustomBl_CheckedChanged()	
	

		//---------------------------------------------------------------------
		// txtCustmBlPlacement_Leave()
		//---------------------------------------------------------------------
        private void txtCustmBlPlacement_Leave(object sender, EventArgs e)
        {
            int iBlPlacementP;

            try {
                iBlPlacementP = int.Parse( txtCustomBlPlacementP.Text );                
            } catch {
                iBlPlacementP = 1;
            }
            
            if ( iBlPlacementP < 1 ) {
                iBlPlacementP = 1;
            }
            txtCustomBlPlacementP.Text = iBlPlacementP.ToString();

            if ( bStartup == false ) {
                DoParse();
            }
        }// txtCustmBlPlacement_Leave()

		
		
		//---------------------------------------------------------------------
		// txtCustmBlSize_Leave()
		//---------------------------------------------------------------------
        private void txtCustmBlSize_Leave(object sender, EventArgs e)
        {
            int iBlSizeP;

            try {
                iBlSizeP = int.Parse( txtCustomBlSizeP.Text );                
            } catch {
                iBlSizeP = 1;
            }
            
            if ( iBlSizeP < 1 ) {
                iBlSizeP = 1;
            }
            txtCustomBlSizeP.Text = iBlSizeP.ToString();

            if ( bStartup == false ) {
                DoParse();
            }
        }// txtCustmBlSize_Leave()

	}// Class: frmDS30Loader
}
