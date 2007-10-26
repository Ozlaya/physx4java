/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
#include <stdio.h>
#include <map>
#include "NxPhysics.h"
#include <iostream>

using namespace std;
/* Header for class physics_Test */
//the scene
NxPhysicsSDK*     physicsSDK = NULL;
//NxScene*  scene = NULL;
//map to hold object

#ifndef _Included_net_physx4java_Test
#define _Included_net_physx4java_Test
#ifdef __cplusplus
std::map<int,NxScene*> scenes;
std::map<int,NxActor*> actors;
std::map<int,NxMaterial*> materials;
std::map<int,NxActorDesc*> actorDesc;
std::map<int,NxJoint*> joints;
std::map<int,NxJointDesc*> jointDesc;
JavaVM * javaVm;

#ifndef JNI_OnLoad_12_DECLARED
#define JNI_OnLoad_12_DECLARED
jint jniOnLoadVersion = 0;
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
	cout<<"VM LOADED";
	javaVm = vm;
	return (jniOnLoadVersion = JNI_VERSION_1_2);
}
#endif /* JNI_OnLoad_12_DECLARED */

/*
Contact report
*/
 class JavaContactReport : public NxUserContactReport    {
	 
	public:
	 JavaContactReport() {
		}
 
	 void onContactNotify(NxContactPair& pair, NxU32 events)        {
		JNIEnv* env = NULL;
		javaVm->AttachCurrentThread((void**) &env, NULL);
		if (env == NULL)  {

			return;
		}
		NxActor  * actor1 =  pair.actors[0];
		NxActor  * actor2 =  pair.actors[1];
		int    * id1 =  (int*)actor1->userData;
		int    * id2 =  (int*)actor2->userData;
	    
		NxVec3 ff = pair.sumFrictionForce;
		NxVec3 nf = pair.sumNormalForce;
		  jclass functionCls = env->FindClass( "net/physx4java/dynamics/collision/CollisionHandling");
		  jmethodID mid = env->GetStaticMethodID(functionCls, "onContactNotify", "(IIIFFFFFF)V");
		  env->CallStaticVoidMethod(functionCls,mid,*id1,*id2,events,ff.x,ff.y,ff.z,nf.x,nf.y,nf.z);
		
	 }    
 };
extern "C" {
#endif
	void addJoint(int id, NxJoint *j) {
		joints[id] = j;
	}
	NxJoint * getJoint(int id) {
		return joints[id];
	}
//std::map<int,NxJointDesc> testjointDesc;
/*	void testaddJointDesc(int id, NxJointDesc &jd) {
		testjointDesc[id] = jd;
	}

	NxJointDesc testgetJointDesc(int id, NxJointDesc &jd) {
		return testjointDesc[id];
	}*/
	void addJointDesc(int id, NxJointDesc *jd) {
		jointDesc[id] = jd;
	}
	void addScene(int id, NxScene *sc) {
		scenes[id] = sc;
	}
	
	NxScene * getScene(int id) {
		return scenes[id];
	}
	NxJointDesc * getJointDesc(int id) {
		return jointDesc[id];
	}
	void addActorDesc(int id, NxActorDesc * a) {
	actorDesc[id]=a;
	}
	void addMaterial(int id, NxMaterial * m) {
	materials[id]=m;
	}
	NxMaterial * getMaterial(int id) {
	return materials[id];
	}
	void addActor(int id, NxActor * actor) {
	actors[id]=actor;
	}
	NxActor * getActor(int id) {
		return actors[id];
	}
static void CreateMeshFromShape(NxSimpleTriangleMesh &triMesh,NxShape *shape)    { 
	 NxBoxShape *boxShape=shape->isBox();
	 if(boxShape!=NULL)        
	 {            
		 NxBox obb=NxBox(NxVec3(0.0f,0.0f,0.0f),boxShape->getDimensions(),NxMat33(NX_IDENTITY_MATRIX));            triMesh.points=new NxVec3[8];            triMesh.numVertices=8;            triMesh.pointStrideBytes=sizeof(NxVec3);            triMesh.numTriangles=2*6;            triMesh.triangles=new NxU32[2*6*3];            triMesh.triangleStrideBytes=sizeof(NxU32)*3;            triMesh.flags=0;            NxComputeBoxPoints(obb,(NxVec3 *)triMesh.points);            
		 memcpy((NxU32 *)triMesh.triangles,NxGetBoxTriangles(),sizeof(NxU32)*2*6*3);        } 
	 else            
		 NX_ASSERT(!"Invalid shape type");
	 NX_ASSERT(triMesh.isValid());
 }

jfloatArray vector3dToJfloatArray(JNIEnv * env,NxVec3 &vec) {
	jfloat buf[3];
	buf[0] = vec.x;
	buf[1] = vec.y;
	buf[2] = vec.z;
	//floatarray to hold result
	jfloatArray result =  env->NewFloatArray(3);
	//copy buffer to result
	env->SetFloatArrayRegion(result,0,3,buf);
	return result;
}


JNIEXPORT void JNICALL Java_net_physx4java_Functions_worldUseCCD
(JNIEnv *, jobject) {
	physicsSDK->setParameter(NX_CONTINUOUS_CD, 1);
}
JNIEXPORT void JNICALL Java_net_physx4java_Functions_worldSetContactPairFlags
(JNIEnv * env,jobject,int sceneId, int actorid1,int actorid2,int flags) {
	NxActor *actor1 = getActor(actorid1);
	NxActor *actor2 = getActor(actorid2);
	NxScene * scene = getScene(sceneId);
	scene->setActorPairFlags(*actor1,*actor2,(NxContactPairFlag)flags);

}
JNIEXPORT void JNICALL Java_net_physx4java_Functions_worldEnableUserContactReport
(JNIEnv * env,jobject,int sceneId) {
	JavaContactReport *  report = new JavaContactReport();
	NxScene * scene = getScene(sceneId);
	scene->setUserContactReport(report);
}
JNIEXPORT void JNICALL Java_net_physx4java_Functions_worldCreateGroundPlane
(JNIEnv *,int sceneId, jobject) {

    // Create a plane with default descriptor
    NxPlaneShapeDesc planeDesc;
    NxActorDesc actorDesc;
	NxScene * scene =getScene(sceneId);
	actorDesc.shapes.pushBack(&planeDesc);
	scene->createActor(actorDesc);
	
	
}
JNIEXPORT void JNICALL Java_net_physx4java_Functions_actorSetSolverIterations
(JNIEnv * env, jobject,int id,int iter) {
	NxActor  * actor  = getActor(id);
	//set iterations
	actor->setSolverIterationCount(iter);
	
}

JNIEXPORT void JNICALL Java_net_physx4java_Functions_actorSetRotation
(JNIEnv * env, jobject,int id,jfloatArray arr) {
	
	
	//convert array
	jfloat buf[9];
    env->GetFloatArrayRegion(arr, 0, 9, buf);
	//convert array to matric
	NxMat33 m;
	m.setRow(0,NxVec3(buf[0],buf[1],buf[2]));
	m.setRow(1,NxVec3(buf[3],buf[4],buf[5]));
	m.setRow(2,NxVec3(buf[6],buf[7],buf[8]));
	//get actor
	NxActor  * actor  = getActor(id);
	//set orientation
	actor->setGlobalOrientation(m);
	
}

JNIEXPORT jfloatArray JNICALL Java_net_physx4java_Functions_actorGetRotation
(JNIEnv * env, jobject,int id) {
	//get actor
	NxActor  * actor = getActor(id);
	NxMat33 m =  actor->getGlobalOrientation();
	NxVec3 row1 = m.getRow(0);
	NxVec3 row2 = m.getRow(1);
	NxVec3 row3 = m.getRow(2);
	jfloat buf[9];
	buf[0] = row1.x;
	buf[1] = row1.y;
	buf[2] = row1.z;
	//
	buf[3] = row2.x;
	buf[4] = row2.y;
	buf[5] = row2.z;
	//
	buf[6] = row3.x;
	buf[7] = row3.y;
	buf[8] = row3.z;
	//floatarray to hold result
	jfloatArray result =  env->NewFloatArray(9);
	//copy buffer to result
	env->SetFloatArrayRegion(result,0,9,buf);
	return result;
	
}

JNIEXPORT void JNICALL Java_net_physx4java_Functions_actorAddForce
(JNIEnv *, jobject,int id,float force_x,float force_y,float force_z) {
	NxActor  * actor = getActor(id);
	NxVec3 forceVec(force_x,force_y,force_z);
	actor->addForce(forceVec);
	
}
JNIEXPORT void JNICALL Java_net_physx4java_Functions_actorSetLinearVelocity
(JNIEnv *, jobject,int id,float vel_x,float vel_y,float vel_z) {
	NxActor  * actor = getActor(id);
	NxVec3 forceVec(vel_x,vel_y,vel_z);
	actor->setLinearVelocity(forceVec);
}
JNIEXPORT void JNICALL Java_net_physx4java_Functions_actorSetAngularVelocity
(JNIEnv *, jobject,int id,float vel_x,float vel_y,float vel_z) {
	NxActor  * actor = getActor(id);
	NxVec3 forceVec(vel_x,vel_y,vel_z);
	actor->setLinearVelocity(forceVec);
}
JNIEXPORT void JNICALL Java_net_physx4java_Functions_actorSetLinearMomentum
(JNIEnv *, jobject,int id,float m_x,float m_y,float m_z) {
	NxActor  * actor = getActor(id);
	NxVec3 forceVec(m_x,m_y,m_z);
	actor->setLinearMomentum(forceVec);
}
JNIEXPORT void JNICALL Java_net_physx4java_Functions_actorSetAngularMomentum
(JNIEnv *, jobject,int id,float m_x,float m_y,float m_z) {
	NxActor  * actor = getActor(id);
	NxVec3 forceVec(m_x,m_y,m_z);
	actor->setAngularMomentum(forceVec);
}
JNIEXPORT jfloatArray JNICALL Java_net_physx4java_Functions_actorGetPosition
(JNIEnv * env, jobject,int id) {
	//get actor
	NxActor  * actor = getActor(id);
	NxVec3 vec  =  actor->getGlobalPosition();
	return vector3dToJfloatArray(env,vec);
}

JNIEXPORT jfloatArray JNICALL Java_net_physx4java_Functions_actorGetLinearVelocity
(JNIEnv * env, jobject,int id) {
	//get actor
	NxActor  * actor = getActor(id);
	//NxShape shape;
	
	
	NxVec3 vec  =  actor->getLinearVelocity();
	return vector3dToJfloatArray(env,vec);
}
JNIEXPORT jfloatArray JNICALL Java_net_physx4java_Functions_actorGetAngularVelocity
(JNIEnv * env, jobject,int id) {
	//get actor
	NxActor  * actor = getActor(id);
	NxVec3 vec  =  actor->getAngularVelocity();
	
	return vector3dToJfloatArray(env,vec);
}
JNIEXPORT jfloatArray JNICALL Java_net_physx4java_Functions_actorGetAngularMomentum
(JNIEnv * env, jobject,int id) {
	//get actor
	NxActor  * actor = getActor(id);
	NxVec3 vec  =  actor->getAngularMomentum();
	return vector3dToJfloatArray(env,vec);
}
JNIEXPORT jfloatArray JNICALL Java_net_physx4java_Functions_actorGetLinearMomentum
(JNIEnv * env, jobject,int id) {
	//get actor
	NxActor  * actor = getActor(id);
	NxVec3 vec  =  actor->getAngularMomentum();
	return vector3dToJfloatArray(env,vec);
}
JNIEXPORT jfloat JNICALL Java_net_physx4java_Functions_actorGetLinearDamping
(JNIEnv * env, jobject,int id) {
	//get actor
	NxActor  * actor = getActor(id);
	return actor->getLinearDamping();
	
}
JNIEXPORT float JNICALL Java_net_physx4java_Functions_actorGetAngularDamping
(JNIEnv * env, jobject,int id) {
	//get actor
	NxActor  * actor = getActor(id);
	return actor->getAngularDamping();
	
}

JNIEXPORT jdouble JNICALL Java_net_physx4java_Functions_actorComputeKineticEnergy
(JNIEnv * env, jobject,int id) {
	//get actor
	NxActor  * actor = getActor(id);
	return actor->computeKineticEnergy();
}
JNIEXPORT void JNICALL Java_net_physx4java_Functions_actorSetLinearDamping
(JNIEnv *, jobject,int id,float damping) {
	NxActor  * actor = getActor(id);
	actor->setLinearDamping(damping);
}
JNIEXPORT void JNICALL Java_net_physx4java_Functions_actorSetAngularDamping
(JNIEnv *, jobject,int id,float damping) {
	NxActor  * actor = getActor(id);
	actor->setAngularDamping(damping);
}
JNIEXPORT void JNICALL Java_net_physx4java_Functions_materialCreateMaterial
(JNIEnv * env,jobject,int sid,int id) {
	//get actor
	NxMaterialDesc desc;
	NxScene * scene = getScene(sid);
	NxMaterial  * m = scene->createMaterial(desc);
	addMaterial(id,m);
}
JNIEXPORT void JNICALL Java_net_physx4java_Functions_materialSetStaticFriction
(JNIEnv * env, jobject,int id,float friction) {
	//get actor
	NxMaterial  * m = getMaterial(id);
	
	m->setStaticFriction(friction);
	
}
JNIEXPORT void JNICALL Java_net_physx4java_Functions_materialSetDynamicFriction
(JNIEnv * env, jobject,int id,float friction) {
	//get actor
	NxMaterial  * m = getMaterial(id);
	m->setDynamicFriction(friction);
}
JNIEXPORT void JNICALL Java_net_physx4java_Functions_materialRestitution
(JNIEnv * env, jobject,int id,float restitution) {
	//get actor
	NxMaterial  * m = getMaterial(id);
	m->setRestitution(restitution);
}

JNIEXPORT void JNICALL Java_net_physx4java_Functions_actorSetMaterial
(JNIEnv * env, jobject,int actorId,int materialId) {
	//get actor
	NxActor * actor = getActor(actorId);
	NxMaterial  * m = getMaterial(materialId);
	NxShape * shape = actor->getShapes()[0];
	shape->setMaterial(m->getMaterialIndex());
	
	//m->setDynamicFriction(friction);
}

/*
 * Class:     physics_World
 * Method:    Create
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_net_physx4java_Functions_worldSetStepTiming
(JNIEnv *,jobject,int sid,float timing) {
	NxScene * scene = getScene(sid);
	scene->setTiming(timing,NX_TIMESTEP_FIXED);
}
//JNIEXPORT void JNICALL Java_net_physx4java_Functions_sdkCreate
/*
 * Class:     physics_World
 * Method:    Create
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_net_physx4java_Functions_worldCreate
(JNIEnv *,jobject,int sid) {
	
	printf("Initializing world\n");
	physicsSDK = NxCreatePhysicsSDK(NX_PHYSICS_SDK_VERSION);
	// Set the physics parameters
	//physicsSDK->setParameter(NX_SKIN_WIDTH, 0.01);
	// Set the debug visualization parameters
	//physicsSDK->setParameter(NX_VISUALIZATION_SCALE, 1);
	//physicsSDK->setParameter(NX_VISUALIZE_COLLISION_SHAPES, 1);
	//physicsSDK->setParameter(NX_VISUALIZE_ACTOR_AXES, 1);
	physicsSDK->setParameter(NX_SKIN_WIDTH,0.5);
	
	
	//physicsSDK->setParameter(NX_SI
	//create scene
	NxSceneDesc sceneDesc;
 	
	sceneDesc.simType				= NX_SIMULATION_HW;
	sceneDesc.flags = sceneDesc.flags|NX_SF_FORCE_CONE_FRICTION;
	sceneDesc.flags = sceneDesc.flags|NX_ADAPTIVE_FORCE;
	sceneDesc.maxIter = 132;
	
	//sceneDesc.gravity               = NxVec3 (0,-9,0);
	//try to create hardware scene
	NxScene * scene = physicsSDK->createScene(sceneDesc);	

	//check if hardware scene was created
	
	if(!scene){ 
		//no, create software scene
		sceneDesc.simType				= NX_SIMULATION_SW; 
		scene = physicsSDK->createScene(sceneDesc);  
		if(!scene) return;
	}
	addScene(sid,scene);
	
	//create groundplane
	//CreateGroundPlane();
}

//
JNIEXPORT void JNICALL Java_net_physx4java_Functions_worldStep
(JNIEnv *, jobject,int sid,float step) {
	
	NxScene * scene = getScene(sid);
	scene->simulate(step);
	scene->flushStream();
	while (!scene->fetchResults(NX_RIGID_BODY_FINISHED, false));
}
//
JNIEXPORT void JNICALL Java_net_physx4java_Functions_worldSetGravity
(JNIEnv *,jobject,int sid, float x,float y,float z) {
	NxScene * scene = getScene(sid);
	scene->setGravity(NxVec3 (x,y,z));
	
}
JNIEXPORT jfloat JNICALL Java_net_physx4java_Functions_worldGetGravityX
(JNIEnv *,jobject,int sid) {
	NxScene * scene = getScene(sid);
	NxVec3 vec;
	scene->getGravity(vec);
	return vec.x;
}
JNIEXPORT jfloat JNICALL Java_net_physx4java_Functions_worldGetGravityY
(JNIEnv *,jobject,int sid) {
	NxVec3 vec;
	NxScene * scene = getScene(sid);
	scene->getGravity(vec);
	return vec.y;
}
JNIEXPORT jfloat JNICALL Java_net_physx4java_Functions_worldGetGravityZ
(JNIEnv *, jobject,int sid) {
	NxScene * scene = getScene(sid);
	NxVec3 vec;
	scene->getGravity(vec);
	return vec.z;
}
JNIEXPORT void JNICALL Java_net_physx4java_Functions_actorCreateAsNoShape
(JNIEnv *, jobject,int sid, int id,bool isDynamic,bool useCDN) {

	NxActorDesc actorDesc;
	//create bodyDesc
	NxBodyDesc bodyDesc;
	
	//craete boxshape
	NxBoxShapeDesc boxDesc;
	boxDesc.dimensions.set(0.01,0.1,0.1);

	actorDesc.shapes.pushBack(&boxDesc);
	//check for static or dynamic (if not dynamic bodyDesc must be null
	if(isDynamic)actorDesc.body = &bodyDesc;
	else
		actorDesc.body  = NULL;

	actorDesc.density = 10;
	
	actorDesc.globalPose.t = NxVec3(0,0,0);		
	//add actordesc
	addActorDesc(id,&actorDesc);
	NxScene * scene = getScene(sid);
	NxActor * actor =  scene->createActor(actorDesc);	
	
	//set id
	actor->userData=new int(id);
	//add actor
	//check for CCD
	if(useCDN) {
		NxShape *shape= actor->getShapes()[0]; 
		NxShapeFlag flag;
		shape->getFlag(flag);
		shape->setFlag(NX_SF_DYNAMIC_DYNAMIC_CCD,true);
		NxSimpleTriangleMesh triMesh;
		 CreateMeshFromShape(triMesh,shape);
		 NxCCDSkeleton *newSkeleton=physicsSDK->createCCDSkeleton(triMesh);        
		 //FreeSimpleMesh(triMesh);        
		 shape->setCCDSkeleton(newSkeleton);
	}
	addActor(id,actor);
	
};
//actor functions
/*
 * Class:     physics_Actor
 * Method:    init
 * Signature: (I)V
 */

JNIEXPORT void JNICALL Java_net_physx4java_Functions_actorCreateAsBoxShape
(JNIEnv *, jobject,int sceneId, int id,bool isDynamic,bool useCDN,float density, float x,float y,float z) {

	// Add a single-shape actor to the scene
	NxActorDesc actorDesc;
	//create bodyDesc
	NxBodyDesc bodyDesc;
	
	//craete boxshape
	NxBoxShapeDesc boxDesc;
	boxDesc.dimensions.set(x,y,z);
	actorDesc.shapes.pushBack(&boxDesc);
	
	//check for static or dynamic (if not dynamic bodyDesc must be null
	if(isDynamic)actorDesc.body = &bodyDesc;
	else
		actorDesc.body  = NULL;

	actorDesc.density = density;
	
	actorDesc.globalPose.t = NxVec3(0,y,0);		
	//add actordesc
	addActorDesc(id,&actorDesc);
	
	NxScene *scene = getScene(sceneId);
	NxActor * actor =  scene->createActor(actorDesc);	
	
	//actor->setSolverIterationCount(120);
	//set id
	actor->userData=new int(id);
	//add actor
	//check for CCD
	if(useCDN) {
		NxShape *shape= actor->getShapes()[0]; 
		NxShapeFlag flag;
		shape->getFlag(flag);
		shape->setFlag(NX_SF_DYNAMIC_DYNAMIC_CCD,true);
		NxSimpleTriangleMesh triMesh;
		 CreateMeshFromShape(triMesh,shape);
		 NxCCDSkeleton *newSkeleton=physicsSDK->createCCDSkeleton(triMesh);        
		 //FreeSimpleMesh(triMesh);        
		 shape->setCCDSkeleton(newSkeleton);
	}
	addActor(id,actor);
	
};
 
JNIEXPORT void JNICALL Java_net_physx4java_Functions_actorCreateAsGroundPlane
(JNIEnv *, jobject,int sceneId,int id,float density) {

	// Add a single-shape actor to the scene
	NxPlaneShapeDesc planeDesc;
    NxActorDesc actorDesc;
	actorDesc.density = density;
    actorDesc.shapes.pushBack(&planeDesc);
	NxScene * scene = getScene(sceneId);
	NxActor * actor =  scene->createActor(actorDesc);
	//set id
	actor->userData = new int(id);
	addActor(id,actor);
};
JNIEXPORT void JNICALL Java_net_physx4java_Functions_actorSetAsStatic
(JNIEnv *, jobject, int id,bool dynamic) {
	NxActor * actor=getActor(id);
	
}
JNIEXPORT jboolean JNICALL Java_net_physx4java_Functions_actorIsDynamic
(JNIEnv *, jobject, int id,bool dynamic) {
	return getActor(id)->isDynamic();
	
}
JNIEXPORT void JNICALL Java_net_physx4java_Functions_actorCreateAsSphereShape
(JNIEnv *, jobject,int sceneId, int id,bool isDynamic, float density,float radius) {
// Add a single-shape actor to the scene
	// Add a single-shape actor to the scene
	NxActorDesc actorDesc;
	NxBodyDesc bodyDesc;

	// The actor has one shape, a box, 1m on a side
	NxSphereShapeDesc sphereDesc;
	sphereDesc.radius = radius;
	actorDesc.shapes.pushBack(&sphereDesc);
	if(isDynamic) actorDesc.body = &bodyDesc;
	else
		actorDesc.body  = NULL;

	actorDesc.density = density;
	actorDesc.globalPose.t = NxVec3(0,radius,0);		
	NxScene * scene = getScene(sceneId);
	NxActor * actor =  scene->createActor(actorDesc);	
	//set id, use "userdata" field
	actor->userData = new int(id);
	addActor(id,actor);

	
};
JNIEXPORT void JNICALL Java_net_physx4java_Functions_actorAddBoxShape
(JNIEnv *, jobject, int id,float x,float y,float z) {
	//get actor
	printf("Creating boxshape\n");
	NxActor * actor =  getActor(id);
	// The actor has one shape, a box, 1m on a side
	
	NxBoxShapeDesc boxDesc;
	boxDesc.dimensions.set(x,y,z);
	//actorDesc.shapes.pushBack(&boxDesc);	
	actor->createShape(boxDesc);
}
JNIEXPORT void JNICALL Java_net_physx4java_Functions_actorAddSphereShape
(JNIEnv *, jobject, int id,float radius) {
	printf("Creating sphereshape\n");
	//get actor
	NxActor * actor =  getActor(id);
	// The actor has one shape, a box, 1m on a side
	NxSphereShapeDesc sphereDesc;
	sphereDesc.radius = radius;
	//actorDesc.shapes.pushBack(&boxDesc);	
	actor->createShape(sphereDesc);
}


/*
 * Class:     physics_Actor
 * Method:    setMass
 * Signature: (F)V
 */
JNIEXPORT void JNICALL Java_net_physx4java_Functions_actorSetMass
(JNIEnv *, jobject obj,int id, double mass)
{

	NxActor * actor = getActor(id);
	actor->setMass(mass);
}



/*
 * Class:     physics_Actor
 * Method:    getMass
 * Signature: ()D
 */
JNIEXPORT jdouble JNICALL Java_net_physx4java_Functions_actorGetMass
(JNIEnv *, jobject obj,int id) {
	return getActor(id)->getMass();
	//return 0;
}





/*
 * Class:     physics_Actor
 * Method:    setPosition
 * Signature: (FFF)V
 */
JNIEXPORT void JNICALL Java_net_physx4java_Functions_actorSetPosition
(JNIEnv *, jobject, int id,float x, float y , float z) {
	getActor(id)->setGlobalPosition(NxVec3(x,y,z));
	
}

	JNIEXPORT void JNICALL Java_net_physx4java_Functions_jointDescSetActors
	(JNIEnv *, jobject, int jointId,int actorId1,int actorId2) {
		//get jointdesc
		NxJointDesc  * desc = getJointDesc(jointId);
		//get actors
		NxActor * actor1 = getActor(actorId1);
		NxActor * actor2 = getActor(actorId2);
		//attach joint
		desc->actor[0] = actor1;
		desc->actor[1] = actor2;
	}
	
	JNIEXPORT void JNICALL Java_net_physx4java_Functions_jointDescSetLocalNormal
		(JNIEnv *env, jobject, int jointId,int index,jfloatArray normal) {
			//convert to float arrays
			jfloat num_buf[3];
			env->GetFloatArrayRegion(normal, 0, 3, num_buf);
			getJointDesc(jointId)->localNormal[index]=NxVec3(num_buf);
			
				
	}
	JNIEXPORT void JNICALL Java_net_physx4java_Functions_jointDescSetLocalAxis
		(JNIEnv *env, jobject, int jointId,int index,jfloatArray normal) {
			//convert to float arrays
			jfloat num_buf[3];
			env->GetFloatArrayRegion(normal, 0, 3, num_buf);
			getJointDesc(jointId)->localAxis[index]=NxVec3(num_buf);
			
				
	}	
			//get jointdesc
		
	
	JNIEXPORT void JNICALL Java_net_physx4java_Functions_jointDescSetLocalAnchor
	(JNIEnv * env, jobject, int jointId,jfloatArray anchor1,jfloatArray anchor2) {
		jfloat num_buf1[3];
		jfloat num_buf2[3];
		env->GetFloatArrayRegion(anchor1, 0, 3, num_buf1);
		env->GetFloatArrayRegion(anchor2, 0, 3, num_buf2);
		NxJointDesc  * desc = getJointDesc(jointId);
		desc->localAnchor[0] = NxVec3(num_buf1);
		desc->localAnchor[1] = NxVec3(num_buf2);
	}
	JNIEXPORT void JNICALL Java_net_physx4java_Functions_jointDescSetGlobalAnchor
	(JNIEnv *env , jobject, int jointId,float x,float y,float z) {
		NxJointDesc  * desc = (NxJointDesc*) getJointDesc(jointId);
		desc->setGlobalAnchor(NxVec3(x,y,z));
		
	}
JNIEXPORT void JNICALL Java_net_physx4java_Functions_jointDescSetGlobalAxis
	(JNIEnv *env , jobject, int jointId,float x,float y,float z) {
		
		NxJointDesc  * desc = getJointDesc(jointId);
		desc->setGlobalAxis(NxVec3(x,y,z));
		
		
	}
/*
 *Create a D6JointDesc
 */
JNIEXPORT void JNICALL Java_net_physx4java_Functions_jointDescD6Create
(JNIEnv *, jobject, int id) {
	
	NxD6JointDesc  * desc = new NxD6JointDesc();
	addJointDesc(id,desc);
}
JNIEXPORT void JNICALL Java_net_physx4java_Functions_jointD6DescSetLinearDegreesOfFreedom
(JNIEnv *, jobject,int jointId, int motion_x,int motion_y,int motion_z) {
	
	
	//get jointdesc
	NxD6JointDesc * desc = (NxD6JointDesc*) getJointDesc(jointId);
	desc->xMotion = (NxD6JointMotion) motion_x;
	desc->yMotion = (NxD6JointMotion) motion_y;
	desc->zMotion = (NxD6JointMotion) motion_z;
	
	
}
JNIEXPORT void JNICALL Java_net_physx4java_Functions_jointD6DescSetAngularDegreesOfFreedom
(JNIEnv *, jobject,int jointId, int twist,int swing1,int swing2) {
	//cout<<"\n LINEAR "<<swing1<<" "<<swing2<<" "<<twist<<" \n";
	//get jointdesc
	NxD6JointDesc * desc = (NxD6JointDesc*) getJointDesc(jointId);
	
	desc->swing1Motion = (NxD6JointMotion) swing1;
	desc->swing2Motion = (NxD6JointMotion) swing2;
	desc->twistMotion  =  (NxD6JointMotion) twist;

}
	void fillJointLimitDesc(NxJointLimitSoftDesc &desc,float value,float restitution,float spring,float damping) {
		desc.value = value;
		desc.restitution = restitution;
		desc.spring = spring;
		desc.damping = damping;
	
}
JNIEXPORT void JNICALL Java_net_physx4java_Functions_jointD6DescSetLinearLimit
(JNIEnv *, jobject,int jointId, float value,float restitution,float spring,float damping) {
	//get jointdesc
	NxJointLimitSoftDesc desc;
	fillJointLimitDesc(desc,value,restitution,spring,damping);
	NxD6JointDesc * jointDesc = (NxD6JointDesc*) getJointDesc(jointId);
	jointDesc->linearLimit = desc;
}
JNIEXPORT void JNICALL Java_net_physx4java_Functions_jointD6DescSetSwing1Limit
(JNIEnv *, jobject,int jointId, float value,float restitution,float spring,float damping) {
	//get jointdesc
	NxJointLimitSoftDesc desc;
	fillJointLimitDesc(desc,value,restitution,spring,damping);
	NxD6JointDesc * jointDesc = (NxD6JointDesc*) getJointDesc(jointId);
	//set limits
	desc.damping = damping;
	desc.spring = spring;
	desc.value = value;
	desc.restitution = restitution;
	jointDesc->swing1Limit = desc;
	
}
JNIEXPORT void JNICALL Java_net_physx4java_Functions_jointD6DescSetSwing2Limit
(JNIEnv *, jobject,int jointId, float value,float restitution,float spring,float damping) {
	//get jointdesc
	NxJointLimitSoftDesc desc;
	fillJointLimitDesc(desc,value,restitution,spring,damping);
	NxD6JointDesc * jointDesc = (NxD6JointDesc*) getJointDesc(jointId);
	
	desc.damping = damping;
	desc.spring = spring;
	desc.value = value;
	desc.restitution = restitution;
	jointDesc->swing2Limit = desc;
}
JNIEXPORT void JNICALL Java_net_physx4java_Functions_jointD6DescSetTwistLimit
(JNIEnv *, jobject,int jointId, float low_value,float low_restitution,float low_spring,float low_damping,float high_value,float high_restitution,float high_spring,float high_damping) {
	//get jointdesc
	//create low
	NxJointLimitSoftDesc lowDesc;
	fillJointLimitDesc(lowDesc,low_value,low_restitution,low_spring,low_damping);
	NxD6JointDesc * jointDesc = (NxD6JointDesc*) getJointDesc(jointId);
	jointDesc->twistLimit.low = lowDesc;
	//create high
	NxJointLimitSoftDesc highDesc;
	fillJointLimitDesc(highDesc,high_value,high_restitution,high_spring,high_damping);
	jointDesc->twistLimit.low = highDesc;
}
void fillJointDriveDesc(NxJointDriveDesc &desc,int driveType,float damping,float forceLimit,float spring) {
	
	desc.driveType = driveType;
	desc.damping = damping;
	desc.forceLimit = forceLimit;
	desc.spring = spring;
}
JNIEXPORT void JNICALL Java_net_physx4java_Functions_jointD6DescSetXDrive
(JNIEnv *, jobject,int jointId,int driveType,float damping,float forceLimit,float spring) {
	NxJointDriveDesc driveDesc;
	fillJointDriveDesc(driveDesc,driveType,damping,forceLimit,spring);
	NxD6JointDesc * jointDesc = (NxD6JointDesc*) getJointDesc(jointId);
	jointDesc->xDrive = driveDesc;
}
JNIEXPORT void JNICALL Java_net_physx4java_Functions_jointD6DescSetYDrive
(JNIEnv *, jobject,int jointId,int driveType,float damping,float forceLimit,float spring) {
	NxJointDriveDesc driveDesc;
	fillJointDriveDesc(driveDesc,driveType,damping,forceLimit,spring);
	NxD6JointDesc * jointDesc = (NxD6JointDesc*) getJointDesc(jointId);
	jointDesc->yDrive = driveDesc;
}
JNIEXPORT void JNICALL Java_net_physx4java_Functions_jointD6DescSetZDrive
(JNIEnv *, jobject,int jointId,int driveType,float damping,float forceLimit,float spring) {
	NxJointDriveDesc driveDesc;
	fillJointDriveDesc(driveDesc,driveType,damping,forceLimit,spring);
	NxD6JointDesc * jointDesc = (NxD6JointDesc*) getJointDesc(jointId);
	jointDesc->zDrive = driveDesc;
}
JNIEXPORT void JNICALL Java_net_physx4java_Functions_jointD6DescSetSwingDrive
(JNIEnv *, jobject,int jointId,int driveType,float damping,float forceLimit,float spring) {
	NxJointDriveDesc driveDesc;
	fillJointDriveDesc(driveDesc,driveType,damping,forceLimit,spring);
	NxD6JointDesc * jointDesc = (NxD6JointDesc*) getJointDesc(jointId);
	jointDesc->swingDrive = driveDesc;
}
JNIEXPORT void JNICALL Java_net_physx4java_Functions_jointD6DescSetTwistDrive
(JNIEnv *, jobject,int jointId,int driveType,float damping,float forceLimit,float spring) {
	NxJointDriveDesc driveDesc;
	fillJointDriveDesc(driveDesc,driveType,damping,forceLimit,spring);
	NxD6JointDesc * jointDesc = (NxD6JointDesc*) getJointDesc(jointId);
	jointDesc->twistDrive = driveDesc;
}
JNIEXPORT void JNICALL Java_net_physx4java_Functions_jointD6DescSetSlerpDrive
(JNIEnv *, jobject,int jointId,int driveType,float damping,float forceLimit,float spring) {
	NxJointDriveDesc driveDesc;
	fillJointDriveDesc(driveDesc,driveType,damping,forceLimit,spring);
	NxD6JointDesc * jointDesc = (NxD6JointDesc*) getJointDesc(jointId);
	jointDesc->slerpDrive = driveDesc;
}
JNIEXPORT void JNICALL Java_net_physx4java_Functions_jointD6SetDrivePosition
(JNIEnv *, jobject,int jointId,float x,float y,float z) {
	NxD6Joint * joint = (NxD6Joint*) getJoint(jointId);
	joint->setDrivePosition(NxVec3(x,y,z));
}
JNIEXPORT void JNICALL Java_net_physx4java_Functions_jointD6SetDriveOrientation
(JNIEnv *, jobject,int jointId,float x,float y,float z,float w) {
	//jfloat buf[9];
    //env->GetFloatArrayRegion(arr, 0, 10, buf);
	NxD6Joint  * joint = (NxD6Joint*) getJoint(jointId);
	 NxQuat q;
	 q.w = w;
	 q.x = x;
	 q.y = y;
	 q.z = z;
	 q.w = 10;
	 joint->setDriveOrientation(q);
}
JNIEXPORT void JNICALL Java_net_physx4java_Functions_jointD6DescSetDriveLinearVelocity
(JNIEnv *, jobject,int jointId,float x,float y,float z) {
	NxD6Joint * joint = (NxD6Joint*) getJoint(jointId);
	joint->setDriveLinearVelocity(NxVec3(x,y,z));
}
JNIEXPORT void JNICALL Java_net_physx4java_Functions_jointD6DescSetDriveAngularVelocity
(JNIEnv *, jobject,int jointId,float x,float y,float z) {
	NxD6Joint * joint = (NxD6Joint*) getJointDesc(jointId);
	joint->setDriveAngularVelocity(NxVec3(x,y,z));
}
JNIEXPORT void JNICALL Java_net_physx4java_Functions_jointD6DescSetProjectionMode
(JNIEnv *, jobject,int jointId,int mode) {
	NxD6JointDesc * jointDesc = (NxD6JointDesc*) getJointDesc(jointId);
	jointDesc->projectionMode = (NxJointProjectionMode) mode;
}
JNIEXPORT void JNICALL Java_net_physx4java_Functions_jointD6DescSetProjectionDistance
(JNIEnv *, jobject,int jointId,float distance) {
	NxD6JointDesc * jointDesc = (NxD6JointDesc*) getJointDesc(jointId);
	jointDesc->projectionDistance = distance;
}
JNIEXPORT void JNICALL Java_net_physx4java_Functions_jointD6DescSetProjectionAngle
(JNIEnv *, jobject,int jointId,float angle) {
	NxD6JointDesc * jointDesc = (NxD6JointDesc*) getJointDesc(jointId);
	jointDesc->projectionAngle = angle;
}
JNIEXPORT void JNICALL Java_net_physx4java_Functions_jointD6DescSetGearRatio
(JNIEnv *, jobject,int jointId,float gearRatio) {
	NxD6JointDesc * jointDesc = (NxD6JointDesc*) getJointDesc(jointId);
	jointDesc->gearRatio = gearRatio;
}
JNIEXPORT void JNICALL Java_net_physx4java_Functions_jointD6DescSetFlags
(JNIEnv *, jobject,int jointId,float flags) {
	NxD6JointDesc * jointDesc = (NxD6JointDesc*) getJointDesc(jointId);
	jointDesc->flags = flags;
	
}

JNIEXPORT void JNICALL Java_net_physx4java_Functions_jointD6DescSetToDefault
(JNIEnv *, jobject,int jointId) {
	NxD6JointDesc * jointDesc = (NxD6JointDesc*) getJointDesc(jointId);
	jointDesc->setToDefault();
}


//joint functions
JNIEXPORT void JNICALL Java_net_physx4java_Functions_jointSetLimitPoint
(JNIEnv *, jobject,int jointId,float x,float y,float z,bool pointIsOnActor2) {
	NxJoint * joint = getJoint(jointId);
	joint->setLimitPoint(NxVec3(x,y,z),pointIsOnActor2);
}
JNIEXPORT void JNICALL Java_net_physx4java_Functions_jointAddLimitPlane
(JNIEnv *, jobject,int jointId,float x1,float y1,float z1,float x2,float y2,float z2,float restitution) {
	NxJoint * joint = getJoint(jointId);
	joint->addLimitPlane(NxVec3(x1,y1,z1),NxVec3(x2,y2,z2),restitution);
}
JNIEXPORT void JNICALL Java_net_physx4java_Functions_jointPurgeLimitPlanes
(JNIEnv *, jobject,int jointId) {
	NxJoint * joint = getJoint(jointId);
	joint->purgeLimitPlanes();
}

JNIEXPORT void JNICALL Java_net_physx4java_Functions_jointResetLimitPlaneIterator
(JNIEnv *, jobject,int jointId) {
	NxJoint * joint = getJoint(jointId);
	joint->resetLimitPlaneIterator();
}
JNIEXPORT bool JNICALL Java_net_physx4java_Functions_jointHasMoreLimitPlanes
(JNIEnv *, jobject,int jointId) {
	NxJoint * joint = getJoint(jointId);
	return joint->hasMoreLimitPlanes();
}

JNIEXPORT bool JNICALL Java_net_physx4java_Functions_jointGetNextLimitPlane
(JNIEnv *,jobject,int jointId,float x,float y,float z,float planeD) {
	NxJoint * joint = getJoint(jointId);
	return joint->getNextLimitPlane(NxVec3(x,y,z),planeD,NULL);
}
JNIEXPORT void JNICALL Java_net_physx4java_Functions_jointRevoluteDescCreate
(JNIEnv *,jobject,int jointId) {
	NxRevoluteJointDesc * desc = new  NxRevoluteJointDesc();
	//desc->flags = NX_RJF_MOTOR_ENABLED;
	addJointDesc(jointId,desc);
}
JNIEXPORT void JNICALL Java_net_physx4java_Functions_jointRevoluteSetLimit
(JNIEnv *,jobject,int jointId,float hardness1,float restitution1,float value1,float hardness2,float restitution2,float value2) {
	NxRevoluteJointDesc * desc = (NxRevoluteJointDesc*)getJointDesc(jointId);
	NxRevoluteJoint * joint = (NxRevoluteJoint *) getJoint(jointId);
	
	NxJointLimitPairDesc limitPair;
	limitPair.low.hardness = hardness1;
	limitPair.low.restitution = restitution1;
	limitPair.low.value = value1;
	//limitPair.low.isValid = true;
	limitPair.high.hardness = hardness2;
	limitPair.high.restitution = restitution2;
	limitPair.high.value = value2;
	//limitPair.high.isValid= true;
	joint->setLimits(limitPair);	
}
JNIEXPORT void JNICALL Java_net_physx4java_Functions_jointRevoluteSetMotor
(JNIEnv *,jobject,int jointId,float velTarget,float maxForce,bool freeSpin) {
	
	//NxMotorDesc motorDesc;
	//NxRevoluteJointDesc * desc = (NxRevoluteJointDesc*)getJointDesc(jointId);
	//desc.flags |= NX_RJF_MOTOR_ENABLED;
	NxRevoluteJoint * j = (NxRevoluteJoint *) getJoint(jointId);
	NxMotorDesc motor;
	j->getMotor(motor);
	motor.maxForce = maxForce;
	motor.velTarget = velTarget;
	motor.freeSpin= freeSpin;
	j->setMotor(motor);
	//cout<<"DESIRED SPEED="<<velTarget<<"\n";

	
	

	//NxRevoluteJointDesc desc = getR
	//j->getMotor(motorDesc);
	//j->setMotor(motor);
	//motorDesc.maxForce = maxForce;
	//motorDesc.velTarget = velTarget;
	//motorDesc.freeSpin = freeSpin;
	//j->setMotor(motorDesc);*/
	
	
}
JNIEXPORT void JNICALL Java_net_physx4java_Functions_jointRevoluteSetSpring
(JNIEnv *,jobject,int jointId,float spring,float damper,float targetValue) {
	NxRevoluteJointDesc * desc = (NxRevoluteJointDesc*)getJointDesc(jointId);
	desc->spring.spring = spring;
	desc->spring.damper = damper;
	desc->spring.targetValue = targetValue;
}
JNIEXPORT void JNICALL Java_net_physx4java_Functions_jointRevoluteSetFlags
(JNIEnv *,jobject,int jointId,int flags) {
	NxRevoluteJoint * j = (NxRevoluteJoint *)getJoint(jointId);
	j->setFlags(flags);
}

JNIEXPORT void JNICALL Java_net_physx4java_Functions_jointRevoluteCreate
(JNIEnv *,jobject,int sid,int jointId) {
	
	///
	NxRevoluteJointDesc * jointDesc = (NxRevoluteJointDesc *)getJointDesc(jointId);
	//jointDesc->
	NxRevoluteJointDesc desc = *jointDesc;
	//desc.flags = NX_RJF_LIMIT_ENABLED;
	//desc.flags = NX_RJF_LIMIT_ENABLED;
	
	//desc.projectionAngle = 0;
	desc.projectionMode = NX_JPM_POINT_MINDIST;
	desc.projectionDistance= 0.1;
	///desc.
	//motors
	NxMotorDesc motorDesc;
	desc.motor = motorDesc;


	//limits
//	NxJointLimitPairDesc limitPair;
//	jointDesc->limit = limitPair;
		
	//
	NxScene * scene = getScene(sid);
	NxRevoluteJoint  * joint = (NxRevoluteJoint*) scene->createJoint( desc);
	//joint->setFlags(NX_RJF_LIMIT_ENABLED);
	addJoint(jointId,joint);
	}	

JNIEXPORT void JNICALL Java_net_physx4java_Functions_jointFixedCreate
(JNIEnv *,jobject,int sid,int jointId,int actorid1,int actorid2) {
	
	///
	NxActor * actor1 = getActor(actorid1);
	NxActor * actor2 = getActor(actorid2);
	
	NxFixedJointDesc   jointDesc;
	
	jointDesc.actor[0]=actor1;
	jointDesc.actor[1]=actor2;
	//jointDesc.
	//
	NxScene * scene = getScene(sid);
	NxJoint * joint =  scene->createJoint(jointDesc);
	
	addJoint(jointId,joint);
	
	
}	
JNIEXPORT void JNICALL Java_net_physx4java_Functions_jointD6Create
(JNIEnv *,jobject,int sid,int jointId) {
	
	///
	NxD6JointDesc * jointDesc = (NxD6JointDesc *)getJointDesc(jointId);
	NxD6JointDesc desc = *jointDesc;
	//
	NxScene * scene = getScene(sid); 
	NxD6Joint  * joint = (NxD6Joint*) scene->createJoint(desc);
	addJoint(jointId,joint);
	
	
}	

JNIEXPORT float JNICALL Java_net_physx4java_Functions_jointRevoluteGetAngle
(JNIEnv *,jobject,int jointId) {
	NxRevoluteJoint * joint = (NxRevoluteJoint*) getJoint(jointId);
	NxReal r =  joint->getAngle();
	//cout<<"ANGLE = "<<r<<"\n";
	return r;
	//cout<<joint->getFlags();
	
	
}
JNIEXPORT float JNICALL Java_net_physx4java_Functions_jointRevoluteGetVelocity
(JNIEnv *,jobject,int jointId) {
	NxRevoluteJoint * joint = (NxRevoluteJoint*) getJoint(jointId);
	return joint->getVelocity();
}

JNIEXPORT void JNICALL Java_net_physx4java_Functions_testRunner
(JNIEnv *, jobject) {
	
}





#ifdef __cplusplus
}
#endif
#endif
