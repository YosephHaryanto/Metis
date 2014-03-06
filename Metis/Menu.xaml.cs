using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Navigation;
using Microsoft.Phone.Controls;
using Microsoft.Phone.Shell;

namespace Metis
{
    public partial class Menu : PhoneApplicationPage
    {
        public Menu()
        {
            InitializeComponent();
        }

        private void About_Click(object sender, EventArgs e)
        {
            NavigationService.Navigate(new Uri("/Setting.xaml",UriKind.Relative));
        }
        protected override void OnBackKeyPress(System.ComponentModel.CancelEventArgs e)
        {
            
            base.OnBackKeyPress(e);
            
        }
    }
}