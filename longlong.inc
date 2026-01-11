#if !defined LONGLONG_INC
#define LONGLONG_INC

#define LONGLONG_MAX_LEN 	20
#define LONG_LONG_MAX_LEN 	20
#define MAX_LONGLONG_LEN 	20
#define MAX_LONG_LONG_LEN	20

enum stlonglong
{
	lllow,
	llhigh,
};

#define ll:<%1> %1[lllow],%1[llhigh]

native llSetValueString(value[], const stringValue[]);
native llGetValueString(value[], const dest[]);
new ll_dest[MAX_LONGLONG_LEN + 15];
stock llGetValueString_t(value[]) {
	llGetValueString(value, ll_dest);
	return 1;
}
#define llGetValueString(%0)					(ll_dest[0] = EOS, llGetValueString_t(%0), ll_dest)

stock llcmp(value[], val)
{
	static Vhigh, Vlow;
	Vhigh = value[llhigh];
	Vlow = value[lllow];

	if (Vhigh != 0)
	{
		if (Vhigh > 0) return 1;
		return -1;
	}
	if (Vlow >= val) return (val < Vlow);
	return -1;
}

stock llcmp64(value[], valuelow, valuehigh)
{
	static Vhigh, Vlow;
	Vhigh = value[llhigh];
	Vlow = value[lllow];

	if (Vhigh != valuehigh)
	{
		if (Vhigh >= valuehigh) return (valuehigh < Vhigh);
		return -1;
	}
	if (Vlow >= valuelow) return (valuelow < Vlow);
	return -1;
}

native llcmpString(value[], const stringValue[]);

native lladd(value[], val);
native lladd64(value[], valuelow, valuehigh);
native lladdString(value[], const stringValue[]);

native llsub(value[], val);
native llsub64(value[], valuelow, valuehigh);
native llsubString(value[], const stringValue[]);

native llmul(value[], val);
native llmul64(value[], valuelow, valuehigh);
native llmulString(value[], const stringValue[]);

#define llcmp(%0,%2,%1)					(llcmp(%0, %1) %2 0)
#define llcmp64(%0,%3,%1,%2) 			(llcmp64(%0, %1, %2) %3 0)
#define llcmpString(%0,%2,%1) 		(llcmpString(%0, %1) %2 0)

#endif

#define valueBigInt(%1)			llGetValueString(%1)
#define GetILPlayerInt(%1,%2) 	llcmp(%1, >=, %2)
#define GetILPlayerStr(%1,%2)	llcmpString(%1, >=, %2)
#define addBytes64(%1,%2)		lladdString(%1, %2)
#define addBytes32(%1,%2)		lladd(%1, %2)
#define mulBytes64(%1,%2)		llmul(%1, %2)

#define resetBigInt(%1)			llSetValueString(%1, "0")

#define formatStrBigInt(%1)		formatStr(llGetValueString(%1))
#define cache_get_field_content_bigint(%1,%2,%3)\
		(resetBigInt(%1),cache_get_field_content(%2,%3,bStr)&&llSetValueString(%1,bStr))


new bStr[32];
stock formatStr(int[], const chars[] = ".", l=-1) {
    new tempStr[64]; 

    if (int[0] == '-') {
        strmid(tempStr, int, 1, strlen(int));
    } else {
        strcat(tempStr, int);
    }

    bStr[0] = '\0', l = strcat(bStr, tempStr);
    while ((l = l - 3) > 0) {
        strins(bStr, chars, l);
    }
    if (int[0] == '-') {
        strins(bStr, "-", 0);
    }
    return bStr;
}
stock formatInt(number, const chars[] = ".")
{
    static number_text[32];
    format(number_text, sizeof(number_text), "%d", number);

    for(new i = (strlen(number_text) - 3); i > (number < 0 ? 1 : 0); i -= 3)
        strins(number_text[i], chars , 0);

    return number_text;
}
stock IsILNumeric(const str[])
{
    new num = strlen(str);

    if(num == 0 || num == 1 && (str[0] == '-' || str[0] == '+'))
        return false;

    for(new inc; inc < num; inc++) {

		if((inc != 0) && (str[inc] == '-' || str[inc] == '+')) return false;
       	else if(('0' <= str[inc] <= '9' && str[inc] != '-' && str[inc] != '+')) continue;
		else return false; 
    }          
    return true;
}