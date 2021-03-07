package filters;

import filters.enums.Compare;
import filters.interfaces.Strategy;
import product.Container;

import java.util.List;
import java.util.stream.Collectors;

public class HeightFilter implements Strategy {
    Double height;
    Compare compare;

    public HeightFilter(Double height, Compare compare) {
        this.height = height;
        this.compare = compare;
    }

    public List<Container> meets(List<Container> containers) {

        return  containers.stream().filter(container -> {
            if(compare.equals(Compare.EQUALS)){
                return container.getHeight().equals(this.height);
            }
            else if(compare.equals(Compare.GREATER)){
                return container.getHeight() > this.height;
            }
            else if(compare.equals(Compare.LESSER)){
                return container.getHeight() < this.height;
            }
            else{
                return false;
            }
        }).collect(Collectors.toList());


    }
}
