package net.physx4java.dynamics.joints;

import net.physx4java.dynamics.actors.Actor;

public class FixedJointDesc extends JointDesc{
	
	public FixedJointDesc() {
		super();
		// TODO Auto-generated constructor stub
	}

	@Override
	public void setActors(Actor actor1, Actor actor2) {
		// TODO Auto-generated method stub
		//super.setActors(actor1, actor2);
		this.actor1 = actor1;
		this.actor2 = actor2;
	}

}
