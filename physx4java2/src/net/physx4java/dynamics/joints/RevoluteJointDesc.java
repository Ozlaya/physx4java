package net.physx4java.dynamics.joints;

import net.physx4java.Functions;

public class RevoluteJointDesc extends JointDesc{

	public RevoluteJointDesc() {
		super();
		Functions.jointRevoluteDescCreate(id);
	}

	
	
}	
