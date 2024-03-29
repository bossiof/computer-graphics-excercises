

void GameLogic(Assignment07 *A, float Ar, glm::mat4 &ViewPrj, glm::mat4 &World) {
	// The procedure must implement the game logic  to move the character in third person.
	// Input:
	// <Assignment07 *A> Pointer to the current assignment code. Required to read the input from the user
	// <float Ar> Aspect ratio of the current window (for the Projection Matrix)
	// Output:
	// <glm::mat4 &ViewPrj> the view-projection matrix of the camera
	// <glm::mat4 &World> the world matrix of the object
	// Parameters
	// Camera FOV-y, Near Plane and Far Plane
	const float FOVy = glm::radians(45.0f);
	const float nearPlane = 0.1f;
	const float farPlane = 100.f;
	
	// Player starting point
	const glm::vec3 StartingPosition = glm::vec3(-41.50, 0.0, -19.5);
	
	// Camera target height and distance
	const float camHeight = 0.25;
	const float camDist = 1.5;
	// Camera Pitch limits
	const float minPitch = glm::radians(-8.75f);
	const float maxPitch = glm::radians(60.0f);
	// Rotation and motion speed
	const float ROT_SPEED = glm::radians(120.0f);
	const float MOVE_SPEED = 2.0f;

	// Integration with the timers and the controllers
	// returns:
	// <float deltaT> the time passed since the last frame
	// <glm::vec3 m> the state of the motion axes of the controllers (-1 <= m.x, m.y, m.z <= 1)
	// <glm::vec3 r> the state of the rotation axes of the controllers (-1 <= r.x, r.y, r.z <= 1)
	// <bool fire> if the user has pressed a fire button (not required in this assginment)
	float deltaT;
	glm::vec3 m = glm::vec3(0.0f), r = glm::vec3(0.0f);
	bool fire = false;
	A->getSixAxis(deltaT, m, r, fire);

	// Game Logic implementation
	// Current Player Position - statc variables make sure thattheri value remain unchanged in subsequent calls to the procedure
	static glm::vec3 Pos = StartingPosition;
	static float CamAlpha = 0.0f,
	CamBeta = 0.0f,
	CamRho = 0.0f;

	CamAlpha = CamAlpha - ROT_SPEED * deltaT * r.y;
	CamBeta  = CamBeta  - ROT_SPEED * deltaT * r.x;
	CamBeta  =  CamBeta < minPitch ? minPitch :
				(CamBeta > maxPitch ? maxPitch : CamBeta);
	CamRho   = CamRho   - ROT_SPEED * deltaT * r.z;
	CamRho   =  CamRho < glm::radians(-180.0f) ? glm::radians(-180.0f) :
				(CamRho > glm::radians( 180.0f) ? glm::radians( 180.0f) : CamRho);

	glm::mat3 CamDir = glm::rotate(glm::mat4(1.0f), CamAlpha, glm::vec3(0,1,0)) *
					glm::rotate(glm::mat4(1.0f), CamBeta,  glm::vec3(1,0,0)) *
					glm::rotate(glm::mat4(1.0f), CamRho,   glm::vec3(0,0,1));

	glm::vec3 ux = glm::rotate(glm::mat4(1.0f), CamAlpha, glm::vec3(0,1,0)) * glm::vec4(1,0,0,1);
	glm::vec3 uz = glm::rotate(glm::mat4(1.0f), CamAlpha, glm::vec3(0,1,0)) * glm::vec4(0,0,-1,1);
	glm::vec3 uy = glm::vec3(0,1,0);

	Pos = Pos + MOVE_SPEED * m.x *ux* deltaT;
	Pos = Pos + MOVE_SPEED * m.y * glm::vec3(0,1,0) * deltaT;
	Pos = Pos + MOVE_SPEED * m.z *uz* deltaT;

	glm::vec3 ObjectPos = Pos+glm::vec3(0,camHeight,0);
	glm::vec3 CamPos = ObjectPos + camDist*
	glm::vec3(glm::rotate(glm::mat4(1),-CamBeta,ux)*
	glm::rotate(glm::mat4(1),CamAlpha,uy)*
	glm::vec4(0,0,1,1));
	// To be done in the assignment
	glm::mat4 camera_shift= glm::mat4(1);
	glm::mat4 Mprj = glm::perspective(FOVy, Ar, nearPlane, farPlane);
	glm::mat4 Mv = glm::lookAt(CamPos,ObjectPos,uy);
		//glm::rotate(glm::mat4(1.0), -CamRho, glm::vec3(0,0,1)) *
		//glm::rotate(glm::mat4(1.0), -CamBeta, glm::vec3(1,0,0)) *
		//glm::rotate(glm::mat4(1.0), -CamAlpha, glm::vec3(0,1,0)) *
		//CamDir * glm::rotate(glm::mat4(1.0), -minPitch, glm::vec3(1,0,0)) *
		//glm::translate(glm::mat4(1.0), glm::vec3(-Pos.x, -camHeight-Pos.y ,-camDist-Pos.z));
	Mprj[1][1] *= -1;
	ViewPrj =Mprj*Mv;

	World = glm::translate(glm::mat4(1.0), glm::vec3(Pos))*glm::rotate(glm::mat4(1.0), CamAlpha, glm::vec3(0, 1, 0));
		
			
}