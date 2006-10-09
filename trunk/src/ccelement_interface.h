#ifndef __CCELEMENT_INTERFACE_H
#define __CCELEMENT_INTERFACE_H

class CCElementInterface
{
public:
    CCElementInterface() {}
    virtual ~CCElementInterface() {}


private:
    CCElementInterface( const CCElementInterface& source );
    void operator = ( const CCElementInterface& source );
};


#endif // __CCELEMENT_INTERFACE_H
