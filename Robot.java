
/*
 * Created by: Gabriel de Oliveira Rohden
 * Version: 1.0.0
 * Date : 05/12/2014
 * Last Edited: 9:40 pm
 */




public class Robot {
	
		//Size of field
		private int mMaxWidth=5;
		private int mMaxHeight=5;
		
		//Position of Robot in field
		private int mPosX=0;
		private int mPosY=0;
		
		private String mCardinalPoint="N";
		
		
		public static void main(String[] args){
			//Assuming that the user will use an Array command I'll concatenate the String[] into String
			String command = "";
			if(args.length!=0){
				command="";
				for(String string:args){
					command+=string;
				}
				
				Robot robot=new Robot();			
				robot.MoveRobot(command.toUpperCase());
			} 	else{
			System.out.println("\n Forgot the parameters?");
			}
			

			
			
		}
		
		public String MoveRobot(String string){
			String[] commandArr = string.split("");
			for(String command:commandArr){
			switch(command){
				case "L":
					setDirectionLeft();
					break;
				case "R":
					setDirectionRight();
					break;
				case "M":
					Move();
					break;
				case ",":break;
				case "": break;
				default:
					System.out.println("This command is not valid: "+command+".");
					System.out.println("Executing the next command.");
					break;
				}
			}
			System.out.println(getPosition());
			return getPosition();
		}

		private void Move() {
			//Y cardinal points
			if(mCardinalPoint=="S" && canMoveDown()){mPosY-=1;}
			if(mCardinalPoint=="N" && canMoveUp()){mPosY+=1;}
			
			//X cardinal points
			if(mCardinalPoint=="W" && canMoveLeft()){mPosX-=1;}
			if(mCardinalPoint=="E" && canMoveRight()){mPosX+=1;}
			
		}
		

		private boolean canMoveRight() {
			if(mPosX>mMaxWidth-1)return false;
			else return true;
		}

		private boolean canMoveLeft() {
			if(mPosX<1)return false;
			else return true;
		}

		private boolean canMoveUp() {
			if(mPosY>mMaxHeight-1)return false;
			else return true;
		}

		private boolean canMoveDown() {
			if(mPosY<1)return false;
			else return true;
		}

		private void setDirectionRight()
		{
			switch (mCardinalPoint){
				case "E":mCardinalPoint="S";break;
				case "W":mCardinalPoint="N";break;
				case "N":mCardinalPoint="E";break;
				case "S":mCardinalPoint="W";break;
				
				}
		}

		private void setDirectionLeft()
		{
			switch (mCardinalPoint){
				case "E":mCardinalPoint="N";break;
				case "W":mCardinalPoint="S";break;
				case "N":mCardinalPoint="W";break;
				case "S":mCardinalPoint="E";break;
			}
		}
		
		public String getPosition(){
			String position=new String();
			position=String.format(
					" x y\n(%d,%d,%s)",mPosX,mPosY,mCardinalPoint);
			return position;
		}
		
		public void setFieldsMaxDimentions(int x, int y){
			this.mMaxHeight=y;
			this.mMaxWidth=x;
		}

}
