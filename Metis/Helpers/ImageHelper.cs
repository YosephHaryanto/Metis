using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Media.Imaging;
using Windows.Storage;
using MetisDll;
using Microsoft.Xna.Framework.Media;
using Microsoft.Phone;
using ImageTools;
using System.IO.IsolatedStorage;
namespace Metis
{
    /// <summary>
    /// 
    /// </summary>
    public class ImageHelper
    {
        /// <summary>
        /// Library used to saving JPEG file format on Photo Gallery
        /// </summary>
        static MediaLibrary library = new MediaLibrary();

        /// <summary>
        /// Variable containing the virtual store for the application
        /// </summary>
        static IsolatedStorageFile isoStore = IsolatedStorageFile.GetUserStoreForApplication();
        /// <summary>
        /// Gets the pixel from image.
        /// </summary>
        /// <param name="bmp">The BMP.</param>
        /// <returns></returns>
        public static List<int> GetPixelFromImage(BitmapImage bmp)
        {
            WriteableBitmap wb = new WriteableBitmap(bmp);
           
            return wb.Pixels.OfType<int>().ToList();
        }

        /// <summary>
        /// Saves the shadow.
        /// </summary>
        /// <param name="image">The image.</param>
        /// <param name="imageName">Name of the image.</param>
        /// 
        public static void SaveShadow(MetisDll.Image image, string imageName)
        {
            WriteableBitmap a = new WriteableBitmap(image.getWidth(), image.getHeight());
            a.FromByteArray(ConvertImageToByteArray(image));
            if (!isoStore.DirectoryExists("shadow"))
                isoStore.CreateDirectory("shadow");
            var pngDest = new System.IO.IsolatedStorage.IsolatedStorageFileStream("shadow\\"+imageName, FileMode.Create, isoStore);
            a.WritePNG(pngDest);
            // Flush the file stream before we close it (shouldn't be required, but just in case).
            pngDest.Flush();
            // Close the file stream.
            pngDest.Close();
        }
        public static bool RenameShadow(string oldname, string newname)
        {
            if (!isoStore.FileExists("shadow\\" + oldname) )
                return false;
            if (isoStore.FileExists("shadow\\" + newname))
                return false;
            isoStore.MoveFile("shadow\\" + oldname,"shadow\\" + newname);
            isoStore.DeleteFile("shadow\\" + oldname);
            return true;

        }
        public static void SaveShadow(BitmapImage image, string imageName)
        {
            WriteableBitmap a = new WriteableBitmap(image);
            if (!isoStore.DirectoryExists("shadow"))
                isoStore.CreateDirectory("shadow");
            int ct = 1;
            char[] delimiter = { '.' };
            string[] ori = imageName.Split(delimiter) ;
            while (isoStore.FileExists("shadow\\"+imageName) )
            {
                imageName = ori[0] + ct.ToString() + ".png";
                ct++;
            }
            var pngDest = new System.IO.IsolatedStorage.IsolatedStorageFileStream("shadow\\" + imageName, FileMode.Create, isoStore);
            a.WritePNG(pngDest);
            // Flush the file stream before we close it (shouldn't be required, but just in case).
            pngDest.Flush();
            // Close the file stream.
            pngDest.Close();
        }
        public static void DeleteShadow(string imageName)
        {
            if (isoStore.FileExists("shadow\\" + imageName))
                isoStore.DeleteFile("shadow\\" + imageName);
        }
        public static void SaveImage(MetisDll.Image image, string imageName)
        {
            WriteableBitmap a = new WriteableBitmap(image.getWidth(), image.getHeight());
            a.FromByteArray(ConvertImageToByteArray(image));
            a.SaveToMediaLibrary(imageName);
        }

        public static BitmapImage ConvertToBitmap( MetisDll.Image image)
        {
            WriteableBitmap a = new WriteableBitmap(image.getWidth(), image.getHeight());
            a.FromByteArray(ConvertImageToByteArray(image));
            BitmapImage bmImage = new BitmapImage();
            using (MemoryStream stream = new MemoryStream())
            {
                a.WritePNG(stream);
                bmImage.SetSource(stream);
            }

            return bmImage;
        }
        /// <summary>
        /// Loads the image.
        /// </summary>
        /// <param name="imageName">Name of the image.</param>
        /// <returns></returns>
        public static MetisDll.Image LoadShadow(string imageName)
        {
            BitmapImage source = new BitmapImage();
            if (!isoStore.DirectoryExists("shadow"))
                isoStore.CreateDirectory("shadow");
            IsolatedStorageFileStream fileStream = isoStore.OpenFile("shadow\\"+imageName, FileMode.Open, FileAccess.Read);
            source.SetSource(fileStream);
            source.CreateOptions = BitmapCreateOptions.None;
      
            WriteableBitmap wb = new WriteableBitmap(source);
            return new MetisDll.Image(wb.Pixels, wb.PixelWidth, wb.PixelHeight);
        }

        public static string[] LoadShadowList()
        {
            if (!isoStore.DirectoryExists("shadow"))
                isoStore.CreateDirectory("shadow");
            string path = Path.Combine("shadow","*.*");
            return isoStore.GetFileNames(path);
        }

        public static BitmapImage[] LoadShadowImageList()
        {
            string[] list = LoadShadowList();
            BitmapImage[] bmp = new BitmapImage[list.Length];
            int ctr = 0;
            foreach (string lst in list )
            {
                BitmapImage source = new BitmapImage();
                if (!isoStore.DirectoryExists("shadow"))
                    isoStore.CreateDirectory("shadow");
                IsolatedStorageFileStream fileStream = isoStore.OpenFile("shadow\\" + lst, FileMode.Open, FileAccess.Read);
                source.SetSource(fileStream);
                source.CreateOptions = BitmapCreateOptions.None;
                int a= source.PixelWidth;
                bmp[ctr++] = source;
                fileStream.Close();
            }
            return bmp;
        }

        /// <summary>
        /// Converts the image to array.
        /// </summary>
        /// <param name="image">The image.</param>
        /// <returns></returns>
        private static byte [][,] ConvertImageToArray(MetisDll.Image image)
        {
            // Init buffer in FluxJpeg format
            int w = image.getWidth() ;
            int h = image.getHeight();
            IList<int> p = image.getImageData();
            byte[][,] pixelsForJpeg = new byte[3][,]; // RGB colors
            pixelsForJpeg[0] = new byte[w, h];
            pixelsForJpeg[1] = new byte[w, h];
            pixelsForJpeg[2] = new byte[w, h];

            // Copy WriteableBitmap data into buffer for FluxJpeg
            int i = 0;
            for (int y = 0; y < h; y++)
            {
                for (int x = 0; x < w; x++)
                {
                    int color = p[i++];
                    pixelsForJpeg[0][x, y] = (byte)(color >> 16); // R
                    pixelsForJpeg[1][x, y] = (byte)(color >> 8);  // G
                    pixelsForJpeg[2][x, y] = (byte)(color);       // B
                }
            }
            return pixelsForJpeg;
        }

        /// <summary>
        /// Converts the image to byte array.
        /// </summary>
        /// <param name="image">The image.</param>
        /// <returns></returns>
        private static byte[] ConvertImageToByteArray(MetisDll.Image image)
        {
            // Init buffer in FluxJpeg format
            int w = image.getWidth();
            int h = image.getHeight();
            int [] p = image.getImageData().ToArray<int>();
            for ( int i = 0; i< p.Length; i++)
            {
                p[i] = 0xFF << 24 | p[i];
            }
            int len = p.Length * 4;
            byte[] result = new byte[len]; // ARGB
            Buffer.BlockCopy(p, 0, result, 0, len);
            return result;
            
        }
    }
}
