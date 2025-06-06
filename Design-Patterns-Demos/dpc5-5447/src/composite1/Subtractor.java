/*
 * This class forms part of the Design Patterns Course by
 * Dr Heinz Kabutz from JavaSpecialists.eu and may not be
 * distributed without written consent.
 *
 * Copyright 2001-2020, Heinz Kabutz, All rights reserved.
 */

package composite1;

public class Subtractor extends BinaryExpression{

    public Subtractor(Expression left, Expression right) {
        super(left, right);
    }

    @Override
    public double getValue() {
        return this.left.getValue() - this.right.getValue();
    }
}
