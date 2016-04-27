import cv2
from dbr import *
import time

def getImageName():
	localtime = time.localtime()
	capturetime = time.strftime("%Y%m%d%H%M%S", localtime)
	return capturetime + ".jpg"

def readBarcode():
	formats = {
		0x3FFL: "OneD",
		0x1L  : "CODE_39",
		0x2L  : "CODE_128",
		0x4L  : "CODE_93",
		0x8L  : "CODABAR",
		0x10L : "ITF",
		0x20L : "EAN_13",
		0x40L : "EAN_8",
		0x80L : "UPC_A",
		0x100L: "UPC_E",
		0x200L: "INDUSTRIAL_25",
		0x2000000L: "PDF417",
		0x8000000L: "DATAMATRIX",
		0x4000000L: "QR_CODE"
	}

	cv2.namedWindow("preview")
	vc = cv2.VideoCapture(0)
	cache = ""
	results = None

	if vc.isOpened(): # try to get the first frame
		initLicense("64E4EE3532B813C8EA8EA5F34E7B4528")
		rval, frame = vc.read()
	else:
	    rval = False

	while rval:
	    cv2.imshow("preview", frame)
	    rval, frame = vc.read()

	    key = cv2.waitKey(20)
	    if key == ord('c'):
			cache = getImageName()
			cv2.imwrite(cache, frame)
			results = decodeFile(cache)
			print "Total count: " + str(len(results))
			for result in results:
				print "barcode format: " + formats[result[0]]
				print "barcode value: " + result[1] + "\n*************************"
	    elif key == 27:
	    	break

	cv2.destroyWindow("preview")

if __name__ == "__main__":
	print "OpenCV version: " + cv2.__version__
	readBarcode()
