package lab1.model;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

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

    public static Complex fromString(String complexInput) {
        Pattern p = Pattern.compile("-?[0-9]+");
        Matcher m = p.matcher(complexInput);
        String real = "0";
        String imag = "0";
        if(m.find()){
            real = m.group(0);
            if(m.find()){
                imag = m.group(0);
            }
        }
        Float realNum = Float.parseFloat(real);
        Float imagNum = Float.parseFloat(imag);

        return new Complex(realNum, imagNum);
    }

    @Override
    public String toString() {
        return String.format("%.2f%s%.2fi", re, (im >= 0 ? "+" : ""), im);
    }
}
