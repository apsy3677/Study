public  Filter {
    Double lenght; //assume unit is m

    
}

public  WeightFilter {
    Double Weight; //assume unit is m
    
    weightGreaterThen(int weight){
        
    }
    weightLesserThen(int weight){
        
    }
    
}

public  HeightFilter {
    Double Weight; //assume unit is m
    
    weightGreaterThen(int weight){
        
    }
    weightLesserThen(int weight){
        
    }
    
}

public class Strategy{
    List< Containers> doOperation(Changeable changes, List<Container> containers);
}[]

public class ContainerWithWeight implements Strategy{
    List< Containers> doOperation(List<Filters> changes, List<Container> containers){
        // here will be code for actual filtering
        // traverse all containers
        foreach(){
            // loop for filter List
            // verify if it is passing filter
        }
    }
}

Public Class FilterContainers{
    
    private Strategy strategy;
    private List [] Filters;
    
    public FilterContainers(){
        
    }
    
    piblic List<Container> filterList(List<Container> containers, Filters[]){
        
    }
    
    public List<Container> executeStrategy(){
        return strategy.doOperation(changes, containers)
    }
    
}