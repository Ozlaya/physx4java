package net.physx4java;

import javax.vecmath.Matrix3f;
import javax.vecmath.Vector3f;

public class Functions {
	/*
	 * Enumerations
	 * 
	 * 
	 */
	public enum NxD6JointMotion {
		NX_D6JOINT_MOTION_LOCKED, // !< The DOF is locked, it does not allow
									// relative motion.
		NX_D6JOINT_MOTION_LIMITED, // !< The DOF is limited, it only allows
									// motion within a specific range.
		NX_D6JOINT_MOTION_FREE
		// !< The DOF is free and has its full range of motions.

	}

	enum NxJointProjectionMode {
		NX_JPM_NONE, // !< don't project this joint
		NX_JPM_POINT_MINDIST, // !< linear and angular minimum distance
								// projection
		NX_JPM_LINEAR_MINDIST, // !< linear only minimum distance projection
		// there may be more modes later
	};

	public enum NxD6JointFlag {
		/**
		 * \brief Drive along the shortest spherical arc.
		 * 
		 * @see NxD6JointDesc.slerpDrive
		 */
		NX_D6JOINT_SLERP_DRIVE(1 << 0),
		/**
		 * \brief Apply gearing to the angular motion, e.g. body 2s angular
		 * motion is twice body 1s etc.
		 * 
		 * @see NxD6JointDesc.gearRatio
		 */
		NX_D6JOINT_GEAR_ENABLED(1 << 1);

		private final int flag;

		NxD6JointFlag(int flag) {
			this.flag = flag;

		}

	};

	

	public static float[] toArray(Matrix3f m) {
		float a[] = new float[9];

		a[0] = m.m00;
		a[1] = m.m01;
		a[2] = m.m02;
		a[3] = m.m10;
		a[4] = m.m11;
		a[5] = m.m12;
		a[6] = m.m20;
		a[7] = m.m21;
		a[8] = m.m22;
		return a;
	}

	// test function
	public static native void testRunner();

	public static float[] toArray(Vector3f v) {
		float a[] = new float[3];
		a[0] = v.x;
		a[1] = v.y;
		a[2] = v.z;
		return a;
	}

	public static native void worldSetStepTiming(float timing);

	public static native void worldCreate();

	// public static native void worldCreateGroundPlane();
	public static void actorSetRotation(int id, Matrix3f m) {
		actorSetRotation(id, toArray(m));
	}

	public static native void actorSetRotation(int id, float[] a);

	public static native float[] actorGetRotation(int id);

	//
	public static native void worldStep(float step);

	//
	public static native void worldSetGravity(float x, float y, float z);

	public static native void worldUseCCD();

	public static native float worldGetGravityX();

	public static native float worldGetGravityY();

	public static native float worldGetGravityZ();

	public static native void actorAddForce(int id, float force_x,
			float force_y, float force_z);

	public static native void actorCreateAsBoxShape(int id, boolean isDynamic,
			boolean useCCD, float x, float y, float z);

	public static native void actorCreateAsSphereShape(int id,
			boolean isDynamic, float radius);

	public static native void actorCreateAsGroundPlane(int id);

	public static native void actorAddBoxShape(int id, float x, float y, float z);

	public static native void actorAddSphereShape(int id, float radius);

	public static native void actorSetMass(int id, double mass);

	public static native double actorGetMass(int id);

	public static native void actorSetPosition(int id, float x, float y, float z);

	public static native void actorSetLinearVelocity(int id, float vel_x,
			float vel_y, float vel_z);

	public static native void actorSetAngularVelocity(int id, float vel_x,
			float vel_y, float vel_z);

	public static native void actorSetLinearMomentum(int id, float m_x,
			float m_y, float m_z);

	public static native void actorSetAngularMomentum(int id, float m_x,
			float m_y, float m_z);

	public static native float[] actorGetPosition(int id);

	public static native float[] actorGetLinearVelocity(int id);

	public static native float[] actorGetAngularVelocity(int id);

	public static native float[] actorGetAngularMomentum(int id);

	public static native float[] actorGetLinearMomentum(int id);

	public static native float actorGetLinearDamping(int id);

	public static native float actorGetAngularDamping(int id);

	public static native double actorComputeKineticEnergy(int id);

	public static native void actorSetLinearDamping(int id, float damping);

	public static native void actorSetAngularDamping(int id, float damping);

	public static native void materialCreateMaterial(int id);

	public static native void materialSetStaticFriction(int id, float friction);

	public static native void materialSetDynamicFriction(int id, float friction);

	public static native void actorSetMaterial(int actorId, int materialId);

	/*
	 * Joints Desc
	 */
	public static native void jointDescSetActors(int jointId, int actorId1,
			int actorId2);
	public static native void jointDescSetGlobalAxis(int jointId, float axis[]); 

	public static native void jointDescSetLocalNormal(int jointId,
			float normal1[], float normal2[]);

	public static native void jointDescSetLocalAnchor(int jointId, float f1[],
			float f2[]);

	public static native void jointDescSetGlobalAnchor(int jointId,
			float anchor[]);

	/*
	 * D6 joint desc
	 */
	/*
	 * Create a D6JointDesc
	 */
	public static native void jointDescD6Create(int id);

	public static native void jointD6DescSetLinearDegreesOfFreedom(int jointId,
			int motion_x, int motion_y, int motion_z);

	public static native void jointD6DescSetAngularDegreesOfFreedom(
			int jointId, int swing1, int swing2, int twist);

	public static native void jointD6DescSetLinearLimit(int jointId,
			float value, float restitution, float spring, float damping);

	public static native void jointD6DescSetSwing1Limit(int jointId,
			float value, float restitution, float spring, float damping);

	public static native void jointD6DescSetSwing2Limit(int jointId,
			float value, float restitution, float spring, float damping);

	public static native void jointD6DescSetTwistLimit(int jointId,
			float low_value, float low_restitution, float low_spring,
			float low_damping, float high_value, float high_restitution,
			float high_spring, float high_damping);

	public static native void jointD6DescSetXDrive(int jointId, int driveType,
			float damping, float forceLimit, float spring);

	public static native void jointD6DescSetYDrive(int jointId, int driveType,
			float damping, float forceLimit, float spring);

	public static native void jointD6DescSetZDrive(int jointId, int driveType,
			float damping, float forceLimit, float spring);

	public static native void jointD6DescSetSwingDrive(int jointId,
			int driveType, float damping, float forceLimit, float spring);

	public static native void jointD6DescSetTwistDrive(int jointId,
			int driveType, float damping, float forceLimit, float spring);

	public static native void jointD6DescSetSlerpDrive(int jointId,
			int driveType, float damping, float forceLimit, float spring);

	public static native void jointD6DescSetDrivePosition(int jointId, float x,
			float y, float z);

	public static native void jointD6DescSetDriveOrientation(int jointId,
			float x, float y, float z, float w);

	public static native void jointD6DescSetDriveLinearVelocity(int jointId,
			float x, float y, float z);

	public static native void jointD6DescSetDriveAngularVelocity(int jointId,
			float x, float y, float z);

	public static native void jointD6DescSetProjectionMode(int jointId, int mode);

	public static native void jointD6DescSetProjectionDistance(int jointId,
			float distance);

	public static native void jointD6DescSetProjectionAngle(int jointId,
			float angle);

	public static native void jointD6DescSetGearRatio(int jointId,
			float gearRatio);

	public static native void jointD6DescSetFlags(int jointId, float flags);

	public static native void jointD6DescSetToDefault(int jointId);

	/*
	 * Joint D6 functions
	 */
	public static native void jointD6Create(int jointId);

	static {
		System.loadLibrary("physx");
	}
}
