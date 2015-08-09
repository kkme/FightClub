#include <String.hpp>

using namespace PWRD::FC;

int main(){

	std::string str = "10324:23:1;324:234:53;3245:42:0;4908:321:133;"; 

	String* s = new String(Element_ELEMENT_TYPE_ITEM_TYPE, str);

	Note("Argu: %s", str.c_str());

	s->Parse();

	string res = s->Serialize();

	string use = "3245";

	string key = "10324";

	Note("Result: str=%s", res.c_str());

	Note("Check TOTAL: key=%s, total=%d", key.c_str(), s->GetTotal(key));

	s->SetUse(use, 2);

	s->SetTotal(key, 252);

	Note("Check TOTAL: key=%s, total=%d", key.c_str(), s->GetTotal(key));

	Note("Check USE: key=%s, use=%d", use.c_str(), s->GetUse(use));

	Note("Result: str=%s", s->Serialize().c_str());

	Note("Check TOTAL: key=%s, total=%d", key.c_str(), s->GetTotal(key));

	Note("Check USE: key=%s, use=%d", use.c_str(), s->GetUse(use));

	Note("GetKeys ALL: keys=%s", s->GetKeys().c_str());
	Note("GetKeys Num: keys=%s, num=30", s->GetKeys(30).c_str());
	Note("GetKeys Index: keys=%s, index=3, num=3", s->GetKeys(3, 3).c_str());

	return 1;

}
