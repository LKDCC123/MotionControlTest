
namespace ChzSD
{
	typedef double sdvector3[3];			// 3D vector
#ifndef nbod
#define nbod 10
#endif
#ifndef ndof
#define ndof 21
#endif

	void sdinit();
	void sdrel2cart(int coord, int body, double point[3], double linchg[3], double rotchg[3]);
	void sdstate(double timein, double qin[ndof], double uin[ndof]);
	void sdpos(int body, double point[3], double position[3]);
	void sdorient(int body, double dircos[3][3]);
	void sdtrans(int inbody, double invector[3], int outbody, double outvector[3]);
	void sdmassmat(double mmat[ndof][ndof]);
	void sdfrcmat(double F[ndof]);
	void sdsys(double* MTOT, double CM[3], double ICM[3][3]);
	void sdacc(int body, double point[3], double acc[3]);
	void sdvel(int body, double point[3], double vel[3]);
	void sdcomptrq(double udotin[12], double trqout[12]);
	void sdfulltrq(double udotin[12], double multin[1], double trqout[12]);
	void sdmom(double LMom[3], double AMom[3], double* KEom);
	void sdgetmass(int body, double* massout);
	void sdangvel(int body, double avel[3]);

	//Chz
	void sdjacobian(int body, double point[3], double J[6][ndof]);
	void sddjacobian(double q[ndof], double dq[ndof], int body, double point[3], double dJ[6][ndof]);
	void sdreset();
	extern const double bodygeoms[nbod][10];

	// Set and System Parameters
	void sdmass(int body, double massin);
	void sdiner(int body, double inerin[3][3]);
	void sdbtj(int joint, double btjin[3]);
	void sditj(int joint, double itjin[3]);

	//typedef enum {
	//	Trunk = 0,
	//	RThigh = 1,
	//	RCalf = 2,
	//	RFoot = 3,
	//	LThigh = 4,
	//	LCalf = 5,
	//	LFoot = 6
	//}BodyInfo;

	//typedef enum {
	//	zTrunk = 0,
	//	yTrunk = 1,
	//	xTrunk = 2,
	//	qzTrunk = 3,
	//	qyTrunk = 4,
	//	qxTrunk = 5,
	//	RHip = 6,
	//	RKnee = 7,
	//	RAnkle = 8,
	//	LHip = 9,
	//	LKnee = 10,
	//	LAnkle = 11,
	//}JointInfo;

	//typedef enum {						// indices into sdinfo reply array
	//	kInfoGROUNDED = 0,				// 1 if system is grounded, 0 if free flying
	//	kInfoNBOD = 1,					// number of bodies (and tree joints)
	//	kInfoNDOF = 2,					// number of tree hinge DOFs
	//	kInfoNC = 3,					// number of constraints
	//	kInfoNLOOP = 4,					// number of loop joints
	//	kInfoNLDOF = 5,					// number of loop hinge DOFs
	//	kInfoNLC = 6,					// number of loop constraints (ign. pres)
	//	kInfoNB = 7,					// number of 6DOF and ball joints in tree
	//	kInfoNLB = 8,					// number of 6DOF and ball joints in loop
	//	kInfoNPRESC = 9,				// number of prescribed motion constraints
	//	kInfoNUSERC = 10,				// number of user constraints
	//	kInfoRANK = 11
	//}				// number of constraints not obv. redundant.
	//kSDInfo;
// user provides this
//}

}