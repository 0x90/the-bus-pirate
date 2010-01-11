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
using System.Xml;
using System.Xml.Serialization;

namespace ds30_Loader_GUI
{
    //---------------------------------------------------------------------------
    // Class: settings
    //---------------------------------------------------------------------------
    [XmlRoot("ds30LoaderSettings")]
    public class clsSettings
    {
		//---------------------------------------------------------------------
		// Options
        //---------------------------------------------------------------------
        private bool bDebugmode;
        public bool Debugmode {
	        get {
		        return bDebugmode;
	        } set {
		        bDebugmode = value;
	        }
        }

        private bool bCheckVerStart;
        public bool CheckVerStart {
	        get {
		        return bCheckVerStart;
	        } set {
		        bCheckVerStart = value;
	        }
        }


		//---------------------------------------------------------------------
		// View options
        //---------------------------------------------------------------------
        private bool bWindowOnTop;
        public bool WindowOnTop {
	        get {
		        return bWindowOnTop;
	        } set {
		        bWindowOnTop = value;
	        }
        }


		//---------------------------------------------------------------------
		// Window size
        //---------------------------------------------------------------------
        private int iWindowWidth;
		public int WindowWidth {
	        get {
		        return iWindowWidth;
	        } set {
		        iWindowWidth = value;
	        }
        }

        private int iWindowHeight;
        public int WindowHeight {
	        get {
		        return iWindowHeight;
	        } set {
		        iWindowHeight = value;
	        }
        }


		//---------------------------------------------------------------------
		// Basic tab
        //---------------------------------------------------------------------
        private string strFilename;		
		public string Filename {
	        get {
		        return strFilename;
	        } set {
		        strFilename = value;
	        }
        }

		//---------------------------------------------------------------------
		// Distribution Specific
		//---------------------------------------------------------------------
    	public DefaultStartSettings DefaultStartSettings { get; set;}
    }

// Class: settings
}
