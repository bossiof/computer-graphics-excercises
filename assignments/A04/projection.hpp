

void SetupProjectionMatrices(Assignment04 *A, float Ar) {
/**************
 Method Matrix(int N, glm::mat4 M) of object A,
 receives in N the number of the matrix that needs to be set, and the matrix in M
***************/

	glm::mat4 S(1),Sc;
	float l = -10;
	float r = 10;
	float b = -10/Ar;
	float t = 10/Ar;
	float n = -50;
	float f = 50;
	glm::mat4 ort = glm::ortho(l,r,b,t,n,f);
	glm::mat4 Ry,Rx;
	// Isometric projection
	Sc = glm::scale(glm::mat4(1.0), glm::vec3(1,-1,1));
	Ry=glm::rotate(S,glm::radians(-45.0f),glm::vec3(0,1,0));
	Rx=glm::rotate(S,glm::radians(35.26f),glm::vec3(1,0,0));
	glm::mat4 MT1= Sc*ort*Rx*Ry;
	A->Matrix(1, MT1); // sets the matrix corresponding to piece 1

	// Dimetric
	Sc = glm::scale(glm::mat4(1.0), glm::vec3(1,-1,1));
	Ry=glm::rotate(S,glm::radians(-45.0f),glm::vec3(0,1,0));
	Rx=glm::rotate(S,glm::radians(45.0f),glm::vec3(1,0,0));
	glm::mat4 MT2= Sc*ort*Rx*Ry;
	A->Matrix(2, MT2); // sets the matrix corresponding to piece 2

	// Trimetric
	S = glm::mat4(1);
	Sc = glm::scale(glm::mat4(1.0), glm::vec3(1,-1,1));
	Ry=glm::rotate(S,glm::radians(-60.0f),glm::vec3(0,1,0));
	Rx=glm::rotate(S,glm::radians(45.0f),glm::vec3(1,0,0));
	glm::mat4 MT3= Sc*ort*Rx*Ry;
	A->Matrix(3, MT3); // sets the matrix corresponding to piece 3

	// Cabinet
	S = glm::mat4(1);
	const float p = 0.5;
	const float alpha = 45.0f;

	glm::mat4 M1 =glm::mat4 (1, 0, -p*cos(glm::radians(alpha)), 0,
	0, 1, -p*sin(glm::radians(alpha)), 0,
	0, 0, 1, 0,
	0, 0, 0, 1);
	glm::mat4 shear = glm::transpose(M1);
	glm::mat4 MT4 = Sc*ort*shear;
	A->Matrix(4, MT4); // sets the matrix corresponding to piece 4

}
