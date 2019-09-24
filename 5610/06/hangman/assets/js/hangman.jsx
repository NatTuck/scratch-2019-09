
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


export default function init_game(root) {
  ReactDOM.render(<Hangman />, root);
}

class Hangman extends React.Component {
  constructor(props) {
    super(props);

    this.state = {
      word: "elephant",
      guesses: "",
      max_guesses: 10,
    };
  }

  guessLetters() {
    return this.state.guesses.split('');
  }

  wordLetters() {
    return this.state.word.split('');
  }

  countWrongGuesses() {
    let count = 0;
    let wl = this.wordLetters();
    _.each(this.guessLetters(), (xx) => {
      if (!wl.includes(xx)) {
        count++;
      }
    });
    return count;
  }

  livesLeft() {
    return this.state.max_guesses - this.countWrongGuesses();
  }

  guess(ev) {
    console.log(ev.target.value);
    let guesses = ev.target.value;
    this.setState(Object.assign({}, this.state, {guesses: guesses}));
  }

  clear() {
    this.setState(Object.assign({}, this.state, {guesses: ""}));
  }

  render() {
    return (
      <div>
        <div className="row">
          <div className="column">
            <Word root={this} second="hello" />
          </div>
          <div className="column">
            <Lives root={this} />
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
                   onChange={this.guess.bind(this)}
                   value={this.state.guesses}
            />
            <button onClick={this.clear.bind(this)}>Clear</button>
          </div>
        </div>
      </div>
    );
  }
}

function Lives({root}) {
  return (
    <div>
      <p><b>Lives Left</b></p>
      <p>{root.livesLeft()}</p>
    </div>
  );
}

function Word(props) {
  let {root} = props;

  let guesses = root.guessLetters();
  let letters = _.map(root.wordLetters(), (xx, ii) => {
    let text = guesses.includes(xx) ? xx : "_";
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
