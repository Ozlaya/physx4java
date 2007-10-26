package net.physx4java.dynamics.actors;

import net.physx4java.Functions;
import net.physx4java.WorldPhysX;

public class SphereActor extends Actor{
	float radius;
	public SphereActor(ActorParameters parameters,WorldPhysX world,float radius) {
		super(world);
		Functions.actorCreateAsSphereShape(world.getId(),id,parameters.isDynamic(),parameters.getDensity(), radius);
		setRadius(radius);
	}
	public float getRadius() {
		return radius;
	}
	public void setRadius(float radius) {
		this.radius = radius;
	}
	
}
