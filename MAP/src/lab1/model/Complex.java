package model;

public class Complex {

    Float re;

    Float im;

    public Complex(Float re, Float im) {
        this.re = re;
        this.im = im;
    }

    public Complex add(Complex other) {
        Complex result = new Complex(0F, 0F);
        result.re = this.re + other.re;
        result.im = this.im + other.im;
        return result;
    }

    public Complex subtract(Complex other) {
        Complex result = new Complex(0F, 0F);
        result.re = this.re - other.re;
        result.im = this.im - other.im;
        return result;
    }

    public Complex multiply(Complex other) {
        Complex result = new Complex(0F, 0F);
        result.re = this.re * other.re - this.im * other.im;
        result.im = this.re * other.im + other.re * this.im;
        return result;
    }

    public Complex divide(Complex other) {
        Complex result = new Complex(0F, 0F);
        result.re = (this.re * other.re + this.im * other.im) / (other.re * other.re + other.im * other.im);
        result.im = (this.im * other.re - this.re * other.im) / (other.re * other.re + other.im * other.im);
        return result;
    }

    public Complex conjugate() {
        Complex result = new Complex(0F, 0F);
        result.re = this.re;
        result.im = - this.im;
        return result;
    }

    @Override
    public String toString() {
        return "%s + %si".formatted(this.re, this.im);
    }
}
