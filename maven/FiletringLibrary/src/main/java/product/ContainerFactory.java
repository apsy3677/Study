package product;

import product.Container;

import java.util.Arrays;
import java.util.List;

public class ContainerFactory {
    public static List<Container> manufactureInBulk(){
        return Arrays.asList(
            new Container(10.0, 20.0, 30.0, 40.0),
            new Container(10.0, 20.0, 20.0, 41.0),
            new Container(10.0, 20.0, 40.0, 45.0),
            new Container(10.0, 20.0, 10.0, 9.0),
            new Container(10.0, 20.0, 25.0, 8.0)

        );
    }
}
