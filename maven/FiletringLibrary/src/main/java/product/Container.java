package product;

public class Container {

    private Double length;
    private Double breadth;
    private Double height;
    private Double weight;

    public Container() {
    }

    public Double getLength() {
        return length;
    }

    public Double getBreadth() {
        return breadth;
    }

    public Double getHeight() {
        return height;
    }

    public Double getWeight() {
        return weight;
    }

    public void setLength(Double length) {
        this.length = length;
    }

    public void setBreadth(Double breadth) {
        this.breadth = breadth;
    }

    public void setHeight(Double height) {
        this.height = height;
    }

    public void setWeight(Double weight) {
        this.weight = weight;
    }

    public Container (Double length, Double breadth, Double height, Double weight){
        this.length = length;
        this.breadth = breadth;
        this.height = height;
        this.weight = weight;
    }

    public void prettyPrint(){

        System.out.println("height ="+ this.height + ";\t length = "+this.length + ";\t breadth = "
                +this.breadth + ";\t Weight = "+this.weight);
    }
}
