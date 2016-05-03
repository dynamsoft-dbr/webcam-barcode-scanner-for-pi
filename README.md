# Barcode Scanner with Raspberry Pi and USB Webcam

The sample demonstrates how to use [Dynamsoft Barcode Reader SDK](http://www.dynamsoft.com/Products/Dynamic-Barcode-Reader.aspx) and Python to build a barcode scanner with Raspberry Pi and USB Webcam.


## Getting Started

### Dynamsoft Barcode Reader for Raspberry Pi
1. Contact [support@dynamsoft.com](mailto:support@dynamsoft.com) to get the download link.
2. Extract the package and generate a symbolic link:

    ```
    sudo ln -s $(DynamsoftBarcodeReader)/lib/libDynamsoftBarcodeReader.so /usr/lib/libDynamsoftBarcodeReader.so
    ```
3. Visit [license page](http://www.dynamsoft.com/CustomerPortal/Account/GetTrialLicense.aspx?Product=DBR) to get a trial license.

### Build Custom Python extension
1. Open **setup.py**. Replace the include and lib paths with yours:

    ```
    include_dirs=['/home/pi/Desktop/dbr/include'],
    library_dirs=['/home/pi/Desktop/dbr/lib'],
    ```
2. Build and install Python extension:

    ```
    python setup.py Build
    sudo python setup.py install
    ```
    ![install custom python extension](http://www.codepool.biz/wp-content/uploads/2016/04/python_module_install.png)

### Install OpenCV for Raspberry Pi
Read [How to install OpenCV 3 on Raspbian Jessie](http://www.pyimagesearch.com/2015/10/26/how-to-install-opencv-3-on-raspbian-jessie/).

### Barcode Scanner
1. Connect webcam to Raspberry Pi.
2. Run **cam_reader.py**:

    ```
    python cam_reader.py
    ```
3. Press key 'C' to capture and read barcode.

    ![Raspberry Pi Node.js Barcode Reader](http://www.codepool.biz/wp-content/uploads/2016/04/rpi_barcode_scanner_result.png)

## Blog
[Raspberry Pi Barcode Scanner with Webcam and Python](http://www.codepool.biz/raspberrypi-barcode-scanner-webcam-python.html)
