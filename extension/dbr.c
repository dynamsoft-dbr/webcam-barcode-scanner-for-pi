#include <Python.h>
#include "If_DBR.h"
#include "BarcodeFormat.h"
#include "BarcodeStructs.h"
#include "ErrorCode.h"

// Barcode format
const char * GetFormatStr(__int64 format)
{
    if (format == CODE_39)
        return "CODE_39";
    if (format == CODE_128)
        return "CODE_128";
    if (format == CODE_93)
        return "CODE_93";
    if (format == CODABAR)
        return "CODABAR";
    if (format == ITF)
        return "ITF";
    if (format == UPC_A)
        return "UPC_A";
    if (format == UPC_E)
        return "UPC_E";
    if (format == EAN_13)
        return "EAN_13";
    if (format == EAN_8)
        return "EAN_8";
    if (format == INDUSTRIAL_25)
        return "INDUSTRIAL_25";
    if (format == QR_CODE)
        return "QR_CODE";
    if (format == PDF417)
        return "PDF417";
    if (format == DATAMATRIX)
        return "DATAMATRIX";
        
    return "UNKNOWN";
}

static PyObject *
initLicense(PyObject *self, PyObject *args)
{
    char *license;
    if (!PyArg_ParseTuple(args, "s", &license)) {
    return NULL;
    }
    printf("License: %s\n", license);
    int ret = DBR_InitLicense(license);
    return Py_BuildValue("i", ret);
}

static PyObject *
decodeFile(PyObject *self, PyObject *args)
{
    char *pFileName;
    if (!PyArg_ParseTuple(args, "s", &pFileName)) {
        return NULL;
    }
    
    // Dynamsoft Barcode Reader: init
    __int64 llFormat = (OneD | QR_CODE | PDF417 | DATAMATRIX);
    int iMaxCount = 0x7FFFFFFF;
    ReaderOptions ro = {0};
    pBarcodeResultArray pResults = NULL;
    
    ro.llBarcodeFormat = llFormat;
    ro.iMaxBarcodesNumPerPage = iMaxCount;

    // Decode barcode image
    int ret = DBR_DecodeFile(pFileName, &ro, &pResults);
    printf("DecodeFile ret: %d\n", ret);
    
    {
        int count = pResults->iBarcodeCount;
        pBarcodeResult* ppBarcodes = pResults->ppBarcodes;
        pBarcodeResult tmp = NULL;

        PyObject* list = PyList_New(count);
        PyObject* result = NULL;
        int i = 0;
        for (; i < count; i++)
        {
            tmp = ppBarcodes[i];
            result = PyString_FromString(tmp->pBarcodeData);
            PyList_SetItem(list, i, Py_BuildValue("iN", (int)tmp->llFormat, result));
        }
        // release memory
        DBR_FreeBarcodeResults(&pResults);
        return list;
    }
    
    return Py_None;
}

static PyMethodDef Methods[] =
{
     {"initLicense", initLicense, METH_VARARGS, NULL},
     {"decodeFile", decodeFile, METH_VARARGS, NULL},
     {NULL, NULL, 0, NULL}
};

PyMODINIT_FUNC
initdbr(void)
{
     (void) Py_InitModule("dbr", Methods);
}
