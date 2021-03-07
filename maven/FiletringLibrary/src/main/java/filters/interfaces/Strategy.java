package filters.interfaces;

import product.Container;

import java.util.List;

public interface Strategy {
    List<Container> meets(List<Container> containers);
}
