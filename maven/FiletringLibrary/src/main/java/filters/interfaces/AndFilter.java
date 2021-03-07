package filters.interfaces;

import product.Container;

import java.util.Arrays;
import java.util.List;

public class AndFilter implements Strategy {
    private List<Strategy> strategies;

    public AndFilter(Strategy... strategies) {
        this.strategies = Arrays.asList(strategies);
    }

    @Override
    public List<Container> meets(List<Container> containers) {
        List<Container> filteredConatiners = containers;

        for(Strategy startegy: strategies){
            filteredConatiners = startegy.meets(filteredConatiners);
        }

        return filteredConatiners;
    }
}
