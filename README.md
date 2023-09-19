# Minimalistic Bookmark Saver

## Purpose

This project aims to provide a simple and minimalistic way to save and organize bookmarks. You can store your bookmarks in a YAML file, and then generate a stylized HTML page that can be easily opened in any web browser.

## Dependencies

- GCC (GNU Compiler Collection)
- libyaml: A YAML 1.1 parser and emitter written in C

To install these dependencies on Ubuntu, you can run:

```bash
sudo apt-get install gcc
sudo apt-get install libyaml-dev
```

## How to Compile

Clone the repository and navigate into its directory. Then, you can compile the program using the following command:

```bash
gcc main.c -lyaml -o generate_html
```

This will create an executable named `generate_html`.

## How to Run

To generate an HTML file from your YAML bookmark file, run:

```bash
./generate_html your-bookmarks.yaml
```

Replace `your-bookmarks.yaml` with the name of the YAML file that contains your bookmarks.

Your YAML file should be formatted like this:

```yaml
links:
  - name: Google
    url: https://www.google.com
  - name: OpenAI
    url: https://www.openai.com
  - name: Wikipedia
    url: https://www.wikipedia.org
```

After running the command, an HTML file named `index.html` will be generated in the same directory. Open this file with a web browser to see your bookmarks displayed in a clean, minimalistic style.

---

Feel free to modify this README to better match your project's specifics.
