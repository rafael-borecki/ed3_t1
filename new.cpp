class Rational
{
    int _numerator, _denominator;

  public:
    Rational(int num, int den) : _numerator(num), _denominator(den) {}
    Rational() : _numerator(0), _denominator(1) {}
    Rational(const Rational &r)
    {
        _numerator = r._numerator;
        _denominator = r._denominator;
    }
    int numerator() { return _numerator; }
    int denominator() { return _denominator; }
    Rational plus(const Rational &b)
    {
        return Rational(_numerator * b._denominator + _denominator * b._numerator,
                        _denominator * b._denominator);
    }
    Rational minus(const Rational &b)
    {
        return Rational(_numerator * b._denominator - _denominator * b._numerator,
                        _denominator * b._denominator);
    }
    Rational times(const Rational &b)
    {
        return Rational(_numerator * b._numerator, _denominator * b._denominator);
    }
    Rational over(const Rational &b)
    {
        return Rational(_numerator * b._denominator, _denominator * b._numerator);
    }
    double to_double() { return (double)_numerator / _denominator; }
};
