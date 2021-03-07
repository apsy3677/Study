package filters;

import filters.enums.Compare;
import filters.interfaces.Strategy;
import product.Container;

import java.util.List;
import java.util.stream.Collectors;

public class WeightFilter implements Strategy {
    Double weight;
    Compare compare;

    public WeightFilter(Double weight, Compare compare) {
        this.weight = weight;
        this.compare = compare;
    }

    public List<Container> meets(List<Container> containers) {
        return containers.stream().filter(container -> {
            if(compare.equals(Compare.EQUALS)){
                return container.getWeight().equals(this.weight);
            }
            else if(compare.equals(Compare.GREATER)){
                return container.getWeight() > this.weight;
            }
            else if(compare.equals(Compare.LESSER)){
                return container.getWeight() < this.weight;
            }
            else{
                return false;
            }
        }).collect(Collectors.toList());
    }
}
