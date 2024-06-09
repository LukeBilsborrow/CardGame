#include "SCardAttributes.h"

bool SCardAttributes::TryAddValue(
    ETemplateAttribute key,
    const std::string& val)
{
    bool isValid = false;
    switch (key)
        {
            case ETemplateAttribute::EType:
                if (mTypeMap.contains(val))
                    {
                        this->mType = mTypeMap.at(val);
                        isValid = true;
                    }
                break;
            case ETemplateAttribute::EName:
                this->mName = val;
                isValid = true;
                break;

            case ETemplateAttribute::EPower:

                try
                    {
                        // Do processing
                        int parsedVal = std::stoi(val);
                        this->mPower = parsedVal;
                        isValid = true;
                    }
                catch (...)
                    {
                        throw;
                        // no action on fail
                    }

                break;
            case ETemplateAttribute::EResilience:
                try
                    {
                        // Do processing
                        int parsedVal = std::stoi(val);
                        this->mResilience = parsedVal;
                        isValid = true;
                    }
                catch (...)
                    {
                        throw;
                        // no action on fail
                    }
                break;
            default:
                break;
        }

    return isValid;
};
