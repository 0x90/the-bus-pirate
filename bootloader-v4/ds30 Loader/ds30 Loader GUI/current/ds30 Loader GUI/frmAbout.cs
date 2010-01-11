using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Reflection;
using System.Windows.Forms;
using ds30Loader;

namespace ds30_Loader_GUI
{
    //---------------------------------------------------------------------------
    // Class: frmAbout
    //---------------------------------------------------------------------------
    partial class frmAbout : Form
    {
        //-----------------------------------------------------------------------
        // Constructor()
        //-----------------------------------------------------------------------
        public frmAbout()
        {
            InitializeComponent();
            
            //lblProductName.Text = "ds30 Loader GUI";
            
            this.lblVersion.Text = frmDS30Loader.verGUI.ToString();
            lblEngineVersion.Text = clsds30Loader.strVersion;

            //lblCopyright.Text = "Copyright © 08-09, Mikael Gustafsson";
        }// Constructor()

    }// Class: frmAbout
}
