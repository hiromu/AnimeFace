#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <stdio.h>

const char *xml = "animeface.xml";
const char *output = "facedetect.avi";

int main(int argc, char **argv)
{
	CvCapture *cap;
	CvHaarClassifierCascade *cascade;
	CvMemStorage *storage;
	CvRect *r;
	CvPoint pt1, pt2;
	CvSeq *faces;
	CvVideoWriter *vw;
	IplImage *img, **images;
	int i, frame;

	storage = cvCreateMemStorage(0);
	if(!(cascade = (CvHaarClassifierCascade *)cvLoad(xml, 0, 0, 0)))
		return -1;
	if(argc < 1 || (cap = cvCreateFileCapture(argv[1])) == 0)
		return -1;

	frame = cvGetCaptureProperty(cap, CV_CAP_PROP_FRAME_COUNT);
	img = cvQueryFrame(cap);
	vw = cvCreateVideoWriter(output, CV_FOURCC('X', 'V', 'I', 'D'),
				 15, cvSize(img->width, img->height), 1);

	do {
		faces = cvHaarDetectObjects(img, cascade, storage,
					1.11, 2, 0, cvSize(0, 0), cvSize(0, 0));

		for (i = 0; i < (faces ? faces->total : 0); i++) {
			r = (CvRect *)cvGetSeqElem(faces, i);
			pt1 = cvPoint(r->x, r->y);
			pt2 = cvPoint(r->x + r->width, r->y + r->height);
			cvRectangle(img, pt1, pt2, CV_RGB(255, 0, 0), 3, 4, 0);
		}
		cvWriteFrame(vw, img);
	} while(img = cvQueryFrame(cap));

	cvReleaseVideoWriter(&vw);
	cvReleaseCapture(&cap);
	return 0;
}
