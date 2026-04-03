
class Cents {
  int m_cents;

public:
  Cents(int cents) : m_cents{cents} {}
  Cents operator-() const;
  int getCents() const { return m_cents; };
};

Cents Cents::operator-() const {
  return m_cents; // implicitly gets converted to Cents with the non explicit
                  // constructor
}

int main() { Cents nickle{5}; }
