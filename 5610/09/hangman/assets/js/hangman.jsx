
import React from 'react';
import ReactDOM from 'react-dom';
import _ from 'lodash';
import $ from 'jquery';

/*
 * App state for Hangman:
 *
 *  {
 *     word: String,      // the correct word
 *     guesses: String,   // the letters guessed so far
 *     max_guesses: Int,  // 10
 *  }
 */


export default function init_game(root, channel) {
  ReactDOM.render(<Hangman channel={channel} />, root);
}

class Hangman extends React.Component {
  constructor(props) {
    super(props);

    this.channel = props.channel;
    this.state = {
      skel: [],
      goods: [],
      bads: [],
      lives: 10,
    };

    this.channel.join()
           .receive("ok", this.onJoin.bind(this))
           .receive("error", resp => { console.log("Unable to join", resp) });
  }

  onJoin({game}) {
    this.setState(game);
  }

  onUpdate({game}) {
    this.setState(game);
  }

  livesLeft() {
    return this.state.lives - this.state.bads.length;
  }

  guessLetters() {
    return this.state.goods.concat(this.state.bads);
  }

  guess(ev) {
    console.log(ev);
    let ll = ev.key;
    console.log("guess", ll);
    this.channel.push("guess", { letter: ll })
        .receive("ok", this.onUpdate.bind(this));
  }

  render() {
    return (
      <div>
        <div className="row">
          <div className="column">
            <Word skel={this.state.skel} />
          </div>
          <div className="column">
            <Lives lives={this.livesLeft()} />
          </div>
        </div>
        <div className="row">
          <div className="column">
            <p><b>Guesses</b></p>
            <p>{this.guessLetters().join(" ")}</p>
          </div>
          <div className="column">
            <p><b>Type Stuff</b></p>
            <input type="text"
                   onKeyDown={this.guess.bind(this)}
            />
          </div>
        </div>
      </div>
    );
  }
}

function Lives({lives}) {
  return (
    <div>
      <p><b>Lives Left</b></p>
      <p>{lives}</p>
    </div>
  );
}

function Word(props) {
  let {skel} = props;

  let letters = _.map(skel, (text, ii) => {
    return (
      <span style={{padding: "1ex"}} key={ii}>
        {text}
      </span>
    );
  });

  return (
    <div>
      <p><b>The Word</b></p>
      <p>{letters}</p>
    </div>
  );
}
