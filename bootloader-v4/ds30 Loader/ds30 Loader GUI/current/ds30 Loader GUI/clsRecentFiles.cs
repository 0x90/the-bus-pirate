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
using System.Text;
using System.Runtime.Serialization;
using System.Collections;
using System.IO;
using System.Xml;
using System.Xml.Serialization;
using System.Windows.Forms;
using System.Drawing;
using GHelper;


namespace ds30_Loader_GUI
{
    //-------------------------------------------------------------------------
    // Class: clsRecentFiles
    //-------------------------------------------------------------------------
    public class clsRecentFiles
    {
        //---------------------------------------------------------------------
        // Private variables
        //---------------------------------------------------------------------
        private Hashtable htRecentFiles = null;
        private ComboBox cboFiles;


        //---------------------------------------------------------------------
        // Constructor()
        //---------------------------------------------------------------------
        public clsRecentFiles()
        {	    
            htRecentFiles = new Hashtable( 9 );
	    }// Constructor()


        //---------------------------------------------------------------------
        // AddFile()
        //---------------------------------------------------------------------
        public void AddFile( string pstrFilename, ref clsRecentFile pobjRecentFile, ref bool pbExisting )
        {	  
            pbExisting = false;

            //            
            if ( htRecentFiles.Contains(pstrFilename) == true ) {
                pobjRecentFile = (clsRecentFile)htRecentFiles[ pstrFilename ];
                pbExisting = true;
                return;
            }

            //
            pobjRecentFile = new clsRecentFile( pstrFilename );

            //
            htRecentFiles.Add( pobjRecentFile.Filename, pobjRecentFile );
            cboFiles.Items.Add ( pobjRecentFile.Filename );
	    }// AddFile()


        //---------------------------------------------------------------------
        // GetFile()
        //---------------------------------------------------------------------
        public clsRecentFile GetFile( string pstrFilename )
        {	  
            if ( htRecentFiles.Contains(pstrFilename) == true ) {
                return (clsRecentFile)htRecentFiles[ pstrFilename ];
            }
             
            return null;
	    }// GetFile()


        //---------------------------------------------------------------------
        // LoadFile()
        //---------------------------------------------------------------------
        private void LoadFile( string pstrFilename, ref clsRecentFile pobjRecentFile )
        {	 
	        //-----------------------------------------------------------------
	        // Deserialize
	        //-----------------------------------------------------------------            
            XmlSerializer xmlSerializer = new XmlSerializer( typeof( clsRecentFile ) );
            TextReader textReader = new StreamReader( pstrFilename );
            try {
                pobjRecentFile = (clsRecentFile)xmlSerializer.Deserialize( textReader );
                htRecentFiles.Add( pobjRecentFile.Filename, pobjRecentFile );
            } catch {
                pobjRecentFile = null;
            }
            textReader.Close();
	    }// LoadFile()


        //---------------------------------------------------------------------
        // LoadFiles()
        //---------------------------------------------------------------------
        public void LoadFiles( string pstrPath )
        {
            string[] strFilenames = Directory.GetFiles(pstrPath, "recentfile*.xml");
            clsRecentFile pobjRecentFile = null;

            foreach ( string strFilename in strFilenames ) {
			    if ( File.Exists(strFilename) == true ) {
                    pobjRecentFile = null;
			        LoadFile( strFilename, ref pobjRecentFile );
                    if ( pobjRecentFile != null ) {
                        cboFiles.Items.Add ( pobjRecentFile.Filename );
                    } else {
                        clsDebugTextbox.OutputInfo( "Failed to load " + strFilename, 0 );
                    }
                }
            }
            AdjustCboDropDownWidth( cboFiles );
	    }// LoadFiles()

        
        //---------------------------------------------------------------------
        // AdjustCboDropDownWidth()
        //---------------------------------------------------------------------
        private void AdjustCboDropDownWidth( ComboBox comboBox )
        {
            //bool isDatabound = comboBox.DataSource != null && comboBox.DisplayMember != null && comboBox.DisplayMember != "";
            int widestWidth = comboBox.DropDownWidth;
            string valueToMeasure;
            int currentWidth;

            using ( Graphics g = comboBox.CreateGraphics() ) {
                for ( int i = 0; i < comboBox.Items.Count; i++ ) {
                    //if ( isDatabound )
                        //valueToMeasure = (string)((DataRowView)comboBox.Items[i])[comboBox.DisplayMember];
                    //else
                        valueToMeasure = (string)comboBox.Items[i];

                    currentWidth = (int)g.MeasureString(valueToMeasure, comboBox.Font).Width;
                    if ( currentWidth > widestWidth) {
                        widestWidth = currentWidth;
                    }
                }
            }
            comboBox.DropDownWidth = widestWidth;
        }// AdjustCboDropDownWidth()


        //---------------------------------------------------------------------
        // SaveFile()
        //---------------------------------------------------------------------
        private void SaveFile( clsRecentFile pobjRecentFile, string pstrFilename )
        {	
            XmlSerializer xmlSerializer = new XmlSerializer( typeof(clsRecentFile) );
            TextWriter textWriter = new StreamWriter( pstrFilename );
            xmlSerializer.Serialize( textWriter, pobjRecentFile );
            textWriter.Close();
        }// SaveFile()


        //---------------------------------------------------------------------
        // SaveFiles()
        //---------------------------------------------------------------------
        public void SaveFiles( string pstrPath )
        {	  
            // Delete old files
            /*{
                string[] strFilenames = Directory.GetFiles(pstrPath, "recentfile*.xml");
                foreach ( string strFilename in strFilenames ) {
                    File.Delete( strFilename );
                }
            }*/

            //
            {
            int iCount = 0;
            string strFilename;
            foreach ( clsRecentFile objRecentFile in htRecentFiles.Values ) {
                strFilename = pstrPath + "\\recentfile" + iCount.ToString() + ".xml";
                SaveFile( objRecentFile, strFilename );
                ++iCount;
            }
            }
	    }// SaveFiles()


        //---------------------------------------------------------------------
        // SetComboBox()
        //---------------------------------------------------------------------
        public void SetComboBox( ComboBox pcboFiles )
        {	  
            cboFiles = pcboFiles;
	    }// SetComboBox()

    }// Class: clsRecentFiles
}
