# Segmentation
This is a segmentation component of a Biomedical Imaging System.
Currently on development phase.

main.cxx acts as the main system/program.

General approach intended for this system is as follows :
1) Convert the Dicom series of 2d Images into one 3d image.
2) Segment the 3d image with watershed segmentation. 
3) Visualize the segmented image in graphs, histograms, vtk,fltk, or imageJ, ITKSnap.
Repeat from step 2 with different parameters to get the right parameter for your image.


NOTE: Not much documentation as of now but most of the system can be understood if looked carefully. But important documentation will be there soon.
