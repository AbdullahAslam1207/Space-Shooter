#include "danger.h"
#include "lives.h"
#include "fire.h"
#include "multiple.h"
class addon:public danger,public live,public fire,public multiple
{
public:
	addon()
	{
	}
};
