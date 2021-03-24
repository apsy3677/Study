package Robot;

public class GameController {

    int Board[][];
    public GameController(int n) {
        Board = new int[n][n];
    }

    public static void main(String[] args) {
        int n = 3;
        GameController gameController = new GameController(n);
        Robot robot = new Robot(new Position(0,0), 0, n);
        String commands[] = new String[] {"Left", "Right", "Move"};

        for(String command : commands){
            robot.move(command);

            System.out.println("Robot Position : x, y, dir :: "+ robot.getPosition().getX() +" " +
                    robot.getPosition().getY() + " " + robot.getDirection());
        }

    }
}
