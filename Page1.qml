import QtQuick 2.7

Page1Form {
    button1.onClicked: {
        console.log("Button Pressed. Entered text: " + textField1.text);

        // m_speech.say(textField1.text);


        ya.prosecc();



    }

    button2.onClicked: {

        ya.get(textField1.text);
    }


    Connections
    {
        target: ya

        onPlayQML:
        {

            console.log(file);

            playMusic1.source = "";

            playMusic1.source = file;


            console.log( playMusic1.source);

        }
    }


    playArea1.onPressed:  { playMusic1.play(),textLol.text = "Ok" }



    playMusic1.onStopped:
    {
        // @disable-check M223
        console.log(playMusic1.status);
    }




    ///////////////////////////////////////////////////////////////////////////////

    button3.onClicked: {
        console.log("Button Pressed. Entered text: " + textField1.text);

        // m_speech.say(textField1.text);


        ya.prosecc2();



    }

    button4.onClicked: {

        ya.get2(textField2.text);
    }


    Connections
    {
        target: ya

        onPlayQML2:
        {

            console.log(file);

            playMusic2.source = "";

            playMusic2.source = file;


            console.log(playMusic2.source);

        }
    }


    playArea2.onPressed:  { playMusic2.play(),textLol2.text = "Ok" }
}


