kinect-sillhouettes
===================

A tutorial for working with silhouettes from the kinect for working with images and video.

The kinect is a very wonderful tool for letting people begin to explore interactive artwork. The creation of these projects sometimes requires an understanding for the techiques of how these things operate. And sometimes the need to understand it caan delay the creation.

This is an attempt to get to the basics of working with the sillhouettes the kinect can generate, and less with the skeletal control or motion systems. This is putting the viewer in the piece.

We are going to explore several options, but they basically boil down to getting the video feed from the kinect, turning it into an image and then working with that image to get the sillhouette. 

These steps can be done with several pieces of software, but I am going to concentrate on using OpenFrameworks and Processing to do this.

Each of these systems has various software which we will be using as well. The kinect part and the other part will be OpenCV.

For now the goals are:

1. load a background image.
2. load a cutout image.
3. open the kinect
4. set up a vertext sharder (will be used for masking cutout with mask)
5. draw the background image.
6. get the kinect image.
7. ignore any pixel outside a certain range in the image (<100 right now)
8. rescale the kinect image to the size of the screen.
9. tie the mask to the cutout using vertex shaders.
10. draw the masked cutout to the screen.
11. repeat

there is an error code that comes up for this. Ignore it. It doesn't seem to make a difference.


