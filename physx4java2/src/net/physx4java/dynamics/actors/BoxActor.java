package net.physx4java.dynamics.actors;

import net.physx4java.Functions;
import net.physx4java.WorldPhysX;

public class BoxActor extends Actor {

	public BoxActor( ActorParameters parameters,WorldPhysX world,float x,float y,float z) {
		super(world);
		Functions.actorCreateAsBoxShape(world.getId(),id,parameters.isDynamic(),parameters.isUseCCD(),parameters.getDensity(), x, y, z);
	}

}
