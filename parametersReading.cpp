#include "parametersReading.h"

void ParametersReading::arenaInit(TiXmlElement *application)
{
    TiXmlElement *arquivoArena = application->FirstChildElement("arquivoDaArena");
    string filename = arquivoArena->FirstChildElement("nome")->GetText();
    string format = arquivoArena->FirstChildElement("tipo")->GetText();
    string path = arquivoArena->FirstChildElement("caminho")->GetText();

    arenaFilename += path + "/" + filename + "." + format;
}

void ParametersReading::jogadorInit(TiXmlElement *application)
{
    TiXmlElement *jogador = application->FirstChildElement("jogador");
    TiXmlAttribute *jogadorAttribute = jogador->FirstAttribute();

    while (jogadorAttribute)
    {
        if (strcmp(jogadorAttribute->Name(), "vel") == 0)
        {
            this->gameRuntime->setPlayerSpeedMult(stof(jogadorAttribute->Value()));
        }
        else if (strcmp(jogadorAttribute->Name(), "velTiro") == 0)
        {
            this->gameRuntime->setPlayerBulletSpeedMult(stof(jogadorAttribute->Value()));
        }

        jogadorAttribute = jogadorAttribute->Next();
    }
}

void ParametersReading::inimigoInit(TiXmlElement *application)
{
    TiXmlElement *inimigo = application->FirstChildElement("inimigo");
    TiXmlAttribute *inimigoAttribute = inimigo->FirstAttribute();

    while (inimigoAttribute)
    {
        if (strcmp(inimigoAttribute->Name(), "vel") == 0)
        {
            this->gameRuntime->setEnemyAirplaneSpeedMult(stof(inimigoAttribute->Value()));
        }
        else if (strcmp(inimigoAttribute->Name(), "velTiro") == 0)
        {
            this->gameRuntime->setEnemyBulletSpeedMult(stof(inimigoAttribute->Value()));
        }
        else if (strcmp(inimigoAttribute->Name(), "freqTiro") == 0)
        {
            this->gameRuntime->setEnemyShotsFrequency(stof(inimigoAttribute->Value()));
        }

        inimigoAttribute = inimigoAttribute->Next();
    }
}

bool ParametersReading::parametersInit(const char *filename)
{
    TiXmlDocument doc(filename);
    bool loadOkay = doc.LoadFile();

    if (loadOkay)
    {
        TiXmlElement *application = doc.RootElement();

        arenaInit(application);
        jogadorInit(application);
        inimigoInit(application);

        return true;
    }
    else
    {
        cout << "Failed to load file" << endl;

        return false;
    }
}

void ParametersReading::windowInit(GLfloat x_size, GLfloat y_size)
{
    this->gameRuntime->setWindowsSize_x(x_size);
    this->gameRuntime->setWindowsSize_y(y_size);
}

void ParametersReading::readCircle(TiXmlElement *circle)
{
    TiXmlAttribute *circleAttribute = circle->FirstAttribute();
    Sphere _sphere;
    string color;

    while (circleAttribute)
    {
        if (strcmp(circleAttribute->Name(), "cx") == 0)
        {
            _sphere.setCenter_x(stof(circleAttribute->Value()));
        }
        else if (strcmp(circleAttribute->Name(), "cy") == 0)
        {
            _sphere.setCenter_y(stof(circleAttribute->Value()));
        }
        else if (strcmp(circleAttribute->Name(), "r") == 0)
        {
            _sphere.setRadius(stof(circleAttribute->Value()));
        }
        else if (strcmp(circleAttribute->Name(), "fill") == 0)
        {
            _sphere.setColor(Color(circleAttribute->Value()));
            color = circleAttribute->Value();
        }
        else if (strcmp(circleAttribute->Name(), "id") == 0)
        {
            _sphere.setId(stoi(circleAttribute->Value()));
        }

        circleAttribute = circleAttribute->Next();
    }

    if (color == string("blue"))
    {
        Circle _circle;
        _circle.setId(_sphere.getId());
        _circle.setCenter_x(_sphere.getCenter_x());
        _circle.setCenter_y(_sphere.getCenter_y());
        _circle.setRadius(_sphere.getRadius());
        _circle.setColor(_sphere.getColor());

        FlightArea flightArea(_circle);
        this->gameRuntime->getGame().setFlightArea(flightArea);

        GLfloat diameter = 2 * _circle.getRadius();
        windowInit(diameter, diameter);
    }
    else if (color == string("green"))
    {
        Player player(_sphere);
        this->gameRuntime->getGame().setPlayer(player);
    }
    else if (color == string("red"))
    {
        FlightEnemy flightEnemy(_sphere, this->gameRuntime->getEnemyAirplaneSpeedMult(), this->gameRuntime->getEnemyBulletSpeedMult(), this->gameRuntime->getEnemyShotsFrequency());
        // FlightEnemy flightEnemy(_circle);
        this->gameRuntime->getGame().addFlightEnemy(flightEnemy);
    }
    else if (color == string("orange"))
    {
        TerrestrialEnemy terrestrialEnemy(_sphere);
        this->gameRuntime->getGame().addTerrestrialEnemy(terrestrialEnemy);
    }
}

Color ParametersReading::readSVGRGBColor(string style)
{
    string delimiter = ":";
    string rgb = style.substr(style.find(delimiter) + 5, 5);
    GLfloat r = stof(rgb.substr(0, 1)) / 255.0;
    GLfloat g = stof(rgb.substr(2, 1)) / 255.0;
    GLfloat b = stof(rgb.substr(4, 1)) / 255.0;

    return Color(r, g, b);
}

void ParametersReading::readLine(TiXmlElement *line)
{
    TiXmlAttribute *lineAttribute = line->FirstAttribute();
    Line _line;

    while (lineAttribute)
    { 
        if (strcmp(lineAttribute->Name(), "x1") == 0)
        {
            _line.setPoint1_x(stof(lineAttribute->Value()));
        }
        else if (strcmp(lineAttribute->Name(), "y1") == 0)
        {
            _line.setPoint1_y(stof(lineAttribute->Value()));
        }
        else if (strcmp(lineAttribute->Name(), "x2") == 0)
        {
            _line.setPoint2_x(stof(lineAttribute->Value()));
        }
        else if (strcmp(lineAttribute->Name(), "y2") == 0)
        {
            _line.setPoint2_y(stof(lineAttribute->Value()));
        }
        else if (strcmp(lineAttribute->Name(), "style") == 0)
        {
            _line.setColor(readSVGRGBColor(lineAttribute->Value()));
        }
        else if (strcmp(lineAttribute->Name(), "id") == 0)
        {
            _line.setId(stoi(lineAttribute->Value()));
        }

        lineAttribute = lineAttribute->Next();
    }

    AirportRunway airportRunway(_line);
    this->gameRuntime->getGame().setAirportRunway(airportRunway);
}

bool ParametersReading::readArenaFile()
{
    TiXmlDocument doc(arenaFilename.c_str());
    bool loadOkay = doc.LoadFile();

    if (loadOkay)
    {
        TiXmlNode *arenaDescription = doc.FirstChildElement("svg");

        TiXmlElement *element = arenaDescription->FirstChildElement();

        for (element; element; element = element->NextSiblingElement())
        {
            if (element->ValueTStr() == "circle")
            {
                readCircle(element);
            }
            else if (element->ValueTStr() == "line")
            {
                readLine(element);
            }
        }

        this->gameRuntime->getGame().getPlayer().setAirplaneSpeedMultiplier(this->gameRuntime->getPlayerAirplaneSpeedMult());
        this->gameRuntime->getGame().getPlayer().setBulletSpeedMultiplier(this->gameRuntime->getPlayerBulletSpeedMult());
        return true;
    }
    else
    {
        cout << "Failed to load file" << endl;

        return false;
    }
}