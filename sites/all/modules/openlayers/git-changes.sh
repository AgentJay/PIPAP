BASEDIR=$(dirname $0)
echo "Changes since $2";
echo "<ul>";
git log $2..$3 --date=short --pretty=format:"<li>%ad: %s (<a href='http://drupalcode.org/project/$1.git/commit/%H'>view commit</a>)</li>" | grep -v Merge
echo "</ul>";
