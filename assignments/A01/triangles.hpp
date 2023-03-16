

void SetupTriangles(Assignment01 *A) {
/**************
 Function Triangle(float x1, float y1, float x2, float y2, float x3, float y3, float r, float g, float b)

 draws a triangle connecting points (x1,y1)  (x2, y2) and (x3, y3), colored with the (r,g,b) specified color.
 vertex are expressed in Normalized screen coordinates, (i.e. in range [-1,+1]), following the Vulkan convention.
 The red, green and blue (r,g,b) values are in the range [0,1].
***************/

	A->Triangle(0.117,0.62, -0.26,0.1, 0.117,-0.4,            1,0,0);//red
	A->Triangle(0.117,-0.4, 0.4,-0.05, 0.117,0.35,            1,1,0);//yellow
	A->Triangle(-0.26,0.1, -0.26,0.85 , 0.25,0.85,            0.05,0.52,0.75);//teal
	A->Triangle(0.117,-0.42, 0.315,-0.16 , 0.485,-0.42,       0.5,0,0.5);//purple down
	A->Triangle(0.117,-0.42, 0.31,-0.675 , 0.485,-0.42,       0.5,0,0.5);//purple up
	A->Triangle(0.117,-0.42, 0.312,-0.675 , 0.117,-0.915,     0.758,0.3375,0.474);//pink
	A->Triangle(0.485,-0.42, 0.312,-0.675 , 0.485,-0.915,     0.05,0.62,0.85);//lighter teal
	A->Triangle(-0.45,0.6, -0.26,0.85 , -0.63,0.85,           0.2,0.55,0);//green 1
	A->Triangle(-0.45,0.6, -0.83 ,0.6 , -0.63,0.85,           0.2,0.55,0);//green 2
    
}
