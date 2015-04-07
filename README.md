# Level editor #

Qt application to create simple levels for 2D platformer. Levels can be created, loaded and saved (you can find level example in downloads). Qt 5.4 version used.

Project was developed as test task for C++ developer vacancy.

## Level description ##

Description of each level is in single file named as `<level name>.level`. Information is described in `json` format. Description example presented below.

```
#!json

{
    "elements": [
        {
            "name": "Player",
            "parameters": [
                {
                    "parameter": "speed",
                    "value": "2,50"
                }
            ],
            "position": {
                "x": 0,
                "y": 0
            }
        },
        {
            "name": "Ladder",
            "parameters": [
                {
                    "parameter": "speed",
                    "value": "1"
                }
            ],
            "position": {
                "x": 5,
                "y": 2
            }
        },
        {
            "name": "Ladder",
            "parameters": [
                {
                    "parameter": "speed",
                    "value": "3"
                }
            ],
            "position": {
                "x": 3,
                "y": 4
            }
        },
        {
            "name": "Wall",
            "parameters": [
                {
                    "parameter": "type",
                    "value": "unbreakable"
                }
            ],
            "position": {
                "x": 10,
                "y": 10
            }
        }
    ],
    "size": {
        "height": 15,
        "width": 30
    }
}
```

Level detailed description:

* **size** - level size
    * *height* - levels's height in elements count
    * *width* - level's width in elements count
* **elements** - list of placed elements
    * *name* - element's name
    * *parameters* - list of parameters' values
        * *parameter* - parameter name
        * *value* - parameter value (always string)
    * *position* - element's position
        * *x* - x position
        * *y* - y position

## Element's creation ##
All elements must be placed in `elements` catalog in application folder. Each element is located in separate folder named as element itself. Each folder must contain text file in json formate, that describes element parameters. Some element description example below.

```
#!json

{
	"picture": "pictureOfElement.jpg",
	"limit": 1,
	"parameters": [
		{
			"name": "someFloat",
			"type": "float",
			"desc": {
				"min": 2.0,
				"max": 5.0
			}
		},
		{
			"name": "somEnum",
			"type": "enum",
			"desc": {
				"values": [
					"common",
					"unbreakable"
				]
			}
		}
	]
}
```
Element's parameters detailed description:

* **picture** - name of picture that presents element. Must be located in element directory.
* **limit** -  limit of element count for one level. If it is 0 - then no limit.
* **parameters** - descriptions of element parameters that can be defined. Each paameter must have elements "name" (parameter name), "type" (parameter type) and "desc" (detailed description of parameter type, differs for each type). For now element can have parameters of two types:
    * *enum* - an be one of the defined values. Default value - first element.
        * values - list of possible values
    * *float* - float-pointer number from range. Default value - minimum from range.
        * min - minimal possible value
        * max - maximal possible value

## Application build ##
Builded application archive can be downloaded [here](https://bitbucket.org/bananamilkshake/level-editor/downloads). It is packaged with all necessary .dll files. Also archive includes some created elements to use for level creation such as Wall (has enum parameter for type), Ladder (has float parameter for speed), Player (start position).

## Level example ##
Example of created level can be found [here](https://bitbucket.org/bananamilkshake/level-editor/downloads). All used elements can be found in application build (upper).

## License ##
This application distributed under GPLv2 license, so you can use it freely for any purposes.