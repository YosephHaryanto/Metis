using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Navigation;
using Microsoft.Phone.Controls;
using Microsoft.Phone.Shell;
using MetisDll;
using System.Collections.ObjectModel;
using System.Windows.Media.Imaging;
using Microsoft.Xna.Framework.Media;
using System.ComponentModel;

namespace Metis
{
    public partial class ManageShadow : PhoneApplicationPage
    {
        public ObservableCollection<ShadowDataModel> shadowModel ;
        IList<MetisDll.Image> shadows = new List<MetisDll.Image>();
        ApplicationBarIconButton selectIcon, sendIcon, receiveIcon, deleteIcon;

        private void CreateApplicationBarItems()
        {
            selectIcon = new ApplicationBarIconButton();
            selectIcon.IconUri = new Uri("/Assets/AppBar/Bullets.png", UriKind.RelativeOrAbsolute);
            selectIcon.Text = "select";
            selectIcon.Click += SelectButton_Click;

            sendIcon = new ApplicationBarIconButton();
            sendIcon.IconUri = new Uri("/Assets/AppBar/send.png", UriKind.RelativeOrAbsolute);
            sendIcon.Text = "send";
            sendIcon.Click += SendButton_Click;

            receiveIcon = new ApplicationBarIconButton();
            receiveIcon.IconUri = new Uri("/Assets/AppBar/download.png", UriKind.RelativeOrAbsolute);
            receiveIcon.Text = "receive";
            receiveIcon.Click += ReceiveButton_Click;

            deleteIcon = new ApplicationBarIconButton();
            deleteIcon.IconUri = new Uri("/Assets/AppBar/close.png", UriKind.RelativeOrAbsolute);
            deleteIcon.Text = "delete";
            deleteIcon.Click += DeleteButton_Click;
        }

        ShadowDataModel _currentPicture = null;

        /// <summary>
        /// Sets or gets the current displayed picture
        /// </summary>
        public ShadowDataModel CurrentPicture
        {
            set
            {
                _currentPicture = value;
                ZoomGrid.DataContext = _currentPicture;
                bool hasPicture = (_currentPicture != null);
                ZoomGrid.Visibility = hasPicture ? Visibility.Visible : Visibility.Collapsed;
                ApplicationBar.IsVisible = !hasPicture;
            }
            get { return _currentPicture; }
        }
        public ManageShadow()
        {
            InitializeComponent();
            LoadData();
            CreateApplicationBarItems();
           // shadowModel.CollectionChanged 
        }

        private void LoadData()
        {
            shadowModel = new ObservableCollection<ShadowDataModel>();
            string[] list = ImageHelper.LoadShadowList();
            BitmapImage[] bmp = ImageHelper.LoadShadowImageList();
            for (int i = 0; i < list.Length; i++)
            {
                shadowModel.Add(new ShadowDataModel(bmp[i], list[i]));
            }
            ShadowList.DataContext = shadowModel;
        }
        private void ReceiveButton_Click(object sender, System.EventArgs e)
        {
        	// TODO: Add event handler implementation here.
            App.ObjectNavigationData = new MetisNavigation(MetisNavigation.STATUS.Receive, new List<ShadowDataModel>());
            NavigationService.Navigate(new Uri("/NFCShadow.xaml", UriKind.RelativeOrAbsolute));
        }
        private void SendButton_Click(object sender, System.EventArgs e)
        {
            List<ShadowDataModel> lstBmp = new List<ShadowDataModel>();
            // TODO: Add event handler implementation here.
            foreach ( ShadowDataModel sdm in ShadowList.SelectedItems)
            {
                lstBmp.Add(sdm);
            }
            App.ObjectNavigationData = new MetisNavigation(MetisNavigation.STATUS.Send, lstBmp) ;

            NavigationService.Navigate(new Uri("/NFCShadow.xaml", UriKind.RelativeOrAbsolute));
        }
        private void DeleteButton_Click(object sender, System.EventArgs e)
        {
            // TODO: Add event handler implementation here.
            foreach (ShadowDataModel sdm in ShadowList.SelectedItems )
            {
                ImageHelper.DeleteShadow(sdm.LineOne);
            }
            LoadData();
        }
        
        private void SelectButton_Click(object sender, System.EventArgs e)
        {
        	// TODO: Add event handler implementation here.
            ShadowList.EnforceIsSelectionEnabled = true;
        }
        private void OnPictureItemTap(object sender, System.EventArgs e)
        {
        	// TODO: Add event handler implementation here.
            FrameworkElement fe = sender as FrameworkElement;
            if (fe != null)
            {
                CurrentPicture = fe.DataContext as ShadowDataModel;
            }
        }
        
        private void OnZoomGridTap(object sender, System.EventArgs e)
        {
            // TODO: Add event handler implementation here.
            //CurrentPicture = null;
        }

      
        protected override void OnBackKeyPress(CancelEventArgs e)
        {
            base.OnBackKeyPress(e);
            if (ShadowList.IsSelectionEnabled)
            {
                ShadowList.EnforceIsSelectionEnabled = false;
                e.Cancel = true;
            }
            else if (CurrentPicture != null)
            {
                CurrentPicture = null;
                e.Cancel = true;
            }
        }
        protected override void OnNavigatedTo(NavigationEventArgs e)
        {
            base.OnNavigatedTo(e);
            MetisNavigation mn = (MetisNavigation)App.ObjectNavigationData;
            if (mn== null)
                return;
            if (mn.sdm == null)
                return;

            foreach (ShadowDataModel sdm  in mn.sdm  )
            {
                shadowModel.Add(sdm);
            }
            mn.sdm = null;
        }
        private void SelectionEnabledChange(object sender, System.Windows.DependencyPropertyChangedEventArgs e)
        {
        	// TODO: Add event handler implementation here.
            SetupApplicationBar();
        }
        void ClearApplicationBar()
        {
            while (ApplicationBar.Buttons.Count > 0)
            {
                ApplicationBar.Buttons.RemoveAt(0);
            }

            while (ApplicationBar.MenuItems.Count > 0)
            {
                ApplicationBar.MenuItems.RemoveAt(0);
            }
        }

        private void SetupApplicationBar()
        {
            ClearApplicationBar();
            if (ShadowList.IsSelectionEnabled)
            {
                ApplicationBar.Buttons.Add(sendIcon);
                ApplicationBar.Buttons.Add(deleteIcon);
                UpdateApplicationBar();
            }
            else
            {
                ApplicationBar.Buttons.Add(receiveIcon);
                ApplicationBar.Buttons.Add(selectIcon);
            }
            ApplicationBar.IsVisible = true;
        }
        void UpdateApplicationBar()
        {
            sendIcon.IsEnabled = deleteIcon.IsEnabled =  ((ShadowList.SelectedItems != null) && (ShadowList.SelectedItems.Count > 0));
        }

        private void SelectionChange(object sender, System.Windows.Controls.SelectionChangedEventArgs e)
        {
        	// TODO: Add event handler implementation here.
            UpdateApplicationBar();
        }

        private void RenameButtonClick(object sender, System.Windows.RoutedEventArgs e)
        {
        	// TODO: Add event handler implementation here.
            CurrentPicture = null;
        }
    }
}