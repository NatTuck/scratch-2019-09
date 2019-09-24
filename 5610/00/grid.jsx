
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
      nn: 0
    };
  }

  click(ii) {
    this.setState({nn: ii});
  }

  render() {
    let rows = [];

    for (let ii = 0; ii < 8; ++ii) {
      let cols = [];
      for (let jj = 0; jj < 8; ++jj) {
        let col = <div class="column">{ii}, {jj}</div>;
        cols.push(col);
      }
      rows.push(
        <div class="row">
          {cols}
        </div>
      );
    }

    /*
    let rows = _.map(
      _.range(0, 8), 
      (ii) => <p>{ii}</p>);
    */

    return (
      <div>
        {rows}
      </div>
    );
  }
}

