package Demo;

import filters.HeightFilter;
import filters.WeightFilter;
import filters.enums.Compare;
import filters.interfaces.AndFilter;
import filters.interfaces.OrFilter;
import filters.interfaces.Strategy;
import product.Container;
import product.ContainerFactory;

import java.util.List;

public class DemoFilters {
    public static void main(String[] args) {
        List<Container> containers = ContainerFactory.manufactureInBulk();

        Strategy filter = new WeightFilter(9.8, Compare.GREATER);
        List<Container> filteredContainers = filter.meets(containers);

        System.out.println("Filtered Results Are ::");
        filteredContainers.stream().forEach(Container::prettyPrint);

        filter = new HeightFilter(12.0, Compare.GREATER);
        filteredContainers = filter.meets(containers);

        System.out.println("Filtered Results Are ::");
        filteredContainers.stream().forEach(Container::prettyPrint);

        filter = new AndFilter(new HeightFilter(22.0, Compare.GREATER),
                                new WeightFilter(8.0, Compare.GREATER));
        filteredContainers = filter.meets(containers);

        System.out.println("Filtered Results Are ::");
        filteredContainers.stream().forEach(Container::prettyPrint);

        filter = new OrFilter(new HeightFilter(22.0, Compare.GREATER),
                new WeightFilter(8.0, Compare.GREATER));
        filteredContainers = filter.meets(containers);

        System.out.println("Filtered Results Are ::");
        filteredContainers.stream().forEach(Container::prettyPrint);
    }
}
