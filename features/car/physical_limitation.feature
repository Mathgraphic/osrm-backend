@routing @car
Feature: Car - Handle physical limitation

    Background:
        Given the profile "car"

    Scenario: Car - Use a narrow way
        Then routability should be
            | highway | width  | narrow | bothw |
            | primary |        |        | x     |
            | primary | narrow |        | x     |
            | primary |        | yes    | x     |
            | primary | 1.8    |        |       |
            | primary | 1.9    |        |       |
            | primary | 2.0    |        | x     |
            | primary | 2.1    |        | x     |
            | primary | 1m     |        |       |
            | primary | 1 m    |        |       |
            | primary | 3 m    |        | x     |
            | primary | 6'     |        |       |
            | primary | 6'0"   |        |       |
            | primary | 6'2"   |        |       |
            | primary | 6'3"   |        | x     |
            | primary | 7'     |        | x     |
            | primary | 7'0"   |        | x     |

    Scenario: Car - Limited by width
        Then routability should be
            | highway | maxwidth:physical | maxwidth | width | est_width | bothw |
            | primary | 1                 |          |       |           |       |
            | primary | 3                 |          |       |           | x     |
            | primary |                   | 1        |       |           |       |
            | primary |                   | 3        |       |           | x     |
            | primary |                   |          | 1     |           |       |
            | primary |                   |          | 3     |           | x     |
            | primary |                   |          |       | 1         |       |
            | primary |                   |          |       | 3         | x     |

    Scenario: Car - Limited by height
        Then routability should be
            | highway | maxheight:physical | maxheight | bothw |
            | primary | 1                  |           |       |
            | primary | 3                  |           | x     |
            | primary |                    | 1         |       |
            | primary |                    | 3         | x     |
