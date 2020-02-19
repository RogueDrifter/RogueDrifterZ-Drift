#if defined Regex_SYS_Included_
   #endinput
#endif

#define Regex_SYS_Included_

/*
Functions:

IsValidRDZ
IsContainingNumbers
IsAnIP
IsAnIPEX
IsAnEmail
IsURL
IsADate

*/

stock IsValidRDZ(string[])
{
    new Regex:r = Regex_New("[A-Z][a-z]+\\[RDZ\\]+");

    new check = Regex_Check(string, r);

    Regex_Delete(r);

    return check;
}

stock IsContainingNumbers(string[])
{
    new Regex:r = Regex_New("^(?=.*\\d).+$");
    new check = Regex_Check(string, r);

    Regex_Delete(r);

    return check;
}

stock IsAnIP(string[])
{
    new Regex:r = Regex_New("^(?=\\d+\\.\\d+\\.\\d+\\.\\d+$)(?:(?:25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9][0-9]|[0-9])\\.?){4}$");
    new check = Regex_Check(string, r);

    Regex_Delete(r);

    return check;
}

stock IsURL(string[])
{
    new Regex:r = Regex_New("/^(https?:\\/\\/)?([\\da-z\\.-]+)\\.([a-z\\.]{2,6})([\\/\\w \\.-]*)*\\/?$/");
    new check = Regex_Check(string, r);

    Regex_Delete(r);

    return check;
}

stock IsAnEmail(string[])
{
    new Regex:r = Regex_New("/^([a-z0-9_\\.-]+)@([\\da-z\\.-]+)\\.([a-z\\.]{2,6})$/");
    new check = Regex_Check(string, r);

    Regex_Delete(r);

    return check;
}

stock IsAnIPEx(string[])
{
    new Regex:r = Regex_New("\\b(([01]?\\d?\\d|2[0-4]\\d|25[0-5])\\.){3}([01]?\\d?\\d|2[0-4]\\d|25[0-5])\\b");
    new check = Regex_Check(string, r);

    Regex_Delete(r);

    return check;
}

stock IsADate(string[])
{
    new Regex:r = Regex_New("/^(?:(?:31(\\/|-|\\.)(?:0?[13578]|1[02]|(?:Jan|Mar|May|Jul|Aug|Oct|Dec)))\\1|(?:(?:29|30)(\\/|-|\\.)(?:0?[1,3-9]|1[0-2]|(?:Jan|Mar|Apr|May|Jun|Jul|Aug|Sep|Oct|Nov|Dec))\\2))(?:(?:1[6-9]|[2-9]\\d)?\\d{2})$|^(?:29(\\/|-|\\.)(?:0?2|(?:Feb))\\3(?:(?:(?:1[6-9]|[2-9]\\d)?(?:0[48]|[2468][048]|[13579][26])|(?:(?:16|[2468][048]|[3579][26])00))))$|^(?:0?[1-9]|1\\d|2[0-8])(\\/|-|\\.)(?:(?:0?[1-9]|(?:Jan|Feb|Mar|Apr|May|Jun|Jul|Aug|Sep))|(?:1[0-2]|(?:Oct|Nov|Dec)))\\4(?:(?:1[6-9]|[2-9]\\d)?\\d{2})$/");
    new check = Regex_Check(string, r);

    Regex_Delete(r);

    return check;
}