//Guita Vahdatinia
//gvahdati

#include <cstdlib>
#include <exception>
#include <stack>
#include <stdexcept>
using namespace std;

#include "bigint.h"
#include "debug.h"
#include "relops.h"

bigint::bigint (long that): uvalue (that), is_negative (that < 0) {
   DEBUGF ('~', this << " -> " << uvalue)
}

bigint::bigint (const ubigint& uvalue, bool is_negative):
                uvalue(uvalue), is_negative(is_negative) {
}

bigint::bigint (const string& that) {
   is_negative = that.size() > 0 and that[0] == '_';
   uvalue = ubigint (that.substr (is_negative ? 1 : 0));
}

bigint bigint::operator+ () const {
   return *this;
}

bigint bigint::operator- () const {
   return {uvalue, not is_negative};
}

bigint bigint::operator+ (const bigint& that) const {
  bigint result;
    //check if they have the same sign 
  if(this->is_negative == that.is_negative ){  
    result = uvalue + that.uvalue;
    result.is_negative = that.is_negative;
  }
   else { 
        if (uvalue < that.uvalue) {
            result = that.uvalue - uvalue; 
            result.is_negative = that.is_negative;    
        }   
        else {
            result = uvalue - that.uvalue; 
            result.is_negative = this->is_negative; 
        }   
    }   
   return result;
}

bigint bigint::operator- (const bigint& that) const {
  bigint result;
    //check if they have the same sign 
  if(this->is_negative == that.is_negative ){
    if(uvalue < that.uvalue){
        result = that.uvalue - uvalue;
        if(this->is_negative)
            result.is_negative = false; 
        else
            result.is_negative = true; 
     }    
    else{
        result = uvalue - that.uvalue; 
        if(this->is_negative)
            result.is_negative = true; 
        else
            result.is_negative = false; 
     }    
    }   
    else{
    //if sign is opposite add
        result = uvalue + that.uvalue; 
        result.is_negative = this->is_negative;
    }   
   return result;
}

bigint bigint::operator* (const bigint& that) const {
   bigint result = uvalue * that.uvalue;
    if (that.is_negative == this->is_negative) 
        result.is_negative = false;
    else result.is_negative = true;
   return result;
}

bigint bigint::operator/ (const bigint& that) const {

   bigint result = uvalue / that.uvalue;
    if (that.is_negative == this->is_negative) 
        result.is_negative = false;
    else result.is_negative = true;
   return result;
}

bigint bigint::operator% (const bigint& that) const {

   bigint result = uvalue % that.uvalue;
    if (that.is_negative == this->is_negative) 
        result.is_negative = false;
    else result.is_negative = true;
   return result;
}

bool bigint::operator== (const bigint& that) const {
   return is_negative == that.is_negative and uvalue == that.uvalue;
}

bool bigint::operator< (const bigint& that) const {
   if (is_negative != that.is_negative) return is_negative;
   return is_negative ? uvalue > that.uvalue
                      : uvalue < that.uvalue;
}

ostream& operator<< (ostream& out, const bigint& that) {
   return out << (that.is_negative ? "-" : "")
              <<  that.uvalue;
}
