package filters.interfaces;

import product.Container;

import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;

public class OrFilter implements Strategy {
    List <Strategy> strategies;

    public OrFilter(Strategy... strategies) {
        this.strategies = Arrays.asList(strategies);
    }

    @Override
    public List<Container> meets(List<Container> containers) {
        List <Container> filteredContainers = new LinkedList<>();
        for(Container container: containers){

            for(Strategy strategy: strategies){
                List <Container> temp = strategy.meets(Arrays.asList(container));
                if( temp!= null && (temp.size()>0)){
                    filteredContainers.add(container);
                    break;
                }
            }
        }

        return filteredContainers;
    }
}
