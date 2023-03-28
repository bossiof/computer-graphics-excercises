

void SetupMatrices(Assignment03 *A) {
/**************
 Method Matrix(int N, glm::mat4 M) of object A,
 receives in N the number of the matrix that needs to be set, and the matrix in M
***************/

	glm::mat4 S,T1,R1,R2,R3,Sc1,Sc2;
	
	// To solve the puzzle: scale 2x proportionally, centered in (2,0,-3)
	S = glm::mat4(1);
	T1 = glm::translate(S,glm::vec3(2,0,-3));
	Sc1 = glm::scale(S,glm::vec3(2));
	//T2 = glm::translate(S,glm::vec3(-2,0,3));
	glm::mat4 MT1 = T1*Sc1*inverse(T1);
	A->Matrix(1, MT1); // sets the matrix corresponding to piece 1

	// To solve the puzzle: scale 2x on an axis oriented 45 degrees between the x and z axis and passing through point (1,0,0)
	S = glm::mat4(1);
	T1 = glm::translate(S,glm::vec3(1,0,0));
	R1 = glm::rotate(S,glm::radians(45.0f),glm::vec3(0,1,0));
	Sc1 = glm::scale(S, glm::vec3(3,1,1));
	glm::mat4 MT2=T1*R1*Sc1*glm::inverse(R1)*glm::inverse(T1);
	A->Matrix(2, MT2); // sets the matrix corresponding to piece 2

	// To solve the puzzle: find it yourself! Hint: compose a rotation around an arbitrary point with a translation
	S = glm::mat4(1);
	T1 = glm::translate(S,glm::vec3(-2.55,0,1.3));
	R1 = glm::rotate(S,glm::radians(45.0f),glm::vec3(0,1,0));
	glm::mat4 MT3 = T1*R1;
	A->Matrix(3, MT3); // sets the matrix corresponding to piece 3

	// To solve the puzzle: rotate 60 degree around the y axis, centered in (-1,0,-2)
	S = glm::mat4(1);
	T1 = glm::translate(S,glm::vec3(-1,0,-2));
	R1 = glm::rotate(S,glm::radians(60.0f),glm::vec3(0,1,0));
	glm::mat4 MT4 = T1*R1*glm::inverse(T1);
	A->Matrix(4, MT4); // sets the matrix corresponding to piece 4

	// To solve the puzzle: rotate -90 degree around an arbitrary axis passing in (-1,0,0). The x axis can be aligned to this arbitrary direction with a rotation of -45 around the y axis.	
	S = glm::mat4(1);
	T1 = glm::translate(S,glm::vec3(-1,0,0));
	R1 = glm::rotate(S,glm::radians(-45.0f),glm::vec3(0,1,0));
	R2 = glm::rotate(S,glm::radians(-90.0f),glm::vec3(1,0,0));
	//R3 = glm::rotate(S,glm::radians(-45.0f),glm::vec3(0,0,1));
	glm::mat4 MT5 = T1*R1*R2*glm::inverse(R1)*glm::inverse(T1);
	A->Matrix(5, MT5); // sets the matrix corresponding to piece 5

	// To solve the puzzle: find it yourself! Hint: compose a non-proportional scaling that halves the object along one of the main axes, centered in an arbitrary point, with a translation
	S = glm::mat4(1);
	T1 = glm::translate(S,glm::vec3(1,0,0));
	Sc1 = glm::scale(S, glm::vec3(0.5,1,1));
	glm::mat4 MT6 = T1*Sc1*glm::inverse(T1);
	A->Matrix(6, MT6); // sets the matrix corresponding to piece 6

}
