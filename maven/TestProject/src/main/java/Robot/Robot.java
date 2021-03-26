package Robot;

import lombok.Getter;

@Getter
public class Robot {

    private Position position;
    private int direction;
    private int boardSize;

    public Robot(Position position, int direction, int boardSize) {
        this.position = position;
        this.direction = direction;
        this.boardSize = boardSize;
    }

    public void move(String command){
        //execute command
        if("Left".equals(command) || "Right".equals(command) ){
            changeDir(command);
        }else if("Move".equals(command)){
            int xx = position.getX(),yy=position.getY();

            switch (this.direction){
                case 0 : yy++; break;
                case 1 : xx++; break;
                case 2 : yy--; break;
                case 3 : xx--; break;
            }

            if(isValid(xx,yy)){
                this.position.setX(xx);
                this.position.setY(yy);
            }else{
                System.out.println("Invalid Command: Position not reachable x y "+ xx +" "+ yy);
            }
        }
    }

    private void changeDir(String command) {
        if("Left".equals(command)){
            this.direction = (4 + this.direction -1)%4;
        }else if("Right".equals(command)){
            this.direction = (this.direction + 1)%4;
        }
//        if(this.direction == Direction.EAST){
//            if("left".equals(command)){
//                this.direction = Direction.SOUTH;
//            }else{
//                this.direction = Direction.NORTH;
//            }
//        }else if(this.direction == Direction.WEST){
//            if("left".equals(command)){
//                this.direction = Direction.NORTH;
//            }else{
//                this.direction = Direction.SOUTH;
//            }
//
//        }else if(this.direction == Direction.SOUTH){
//            if("left".equals(command)){
//                this.direction = Direction.EAST;
//            }else{
//                this.direction = Direction.WEST;
//            }
//
//        }else if(this.direction == Direction.NORTH){
//            if("left".equals(command)){
//                this.direction = Direction.EAST;
//            }else{
//                this.direction = Direction.WEST;
//            }
//        }
    }

    private boolean isValid(int xx, int yy) {
        boolean valid = true;
        if(xx<0 || xx >= boardSize || yy<0 || yy >= boardSize){
            return false;
        }
        return valid;
    }
}
