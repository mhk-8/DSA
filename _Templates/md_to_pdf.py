#!/usr/bin/env python3
"""
md_to_pdf.py — turn a DSA notes markdown file into a styled, print-ready PDF.

Usage:
    python3 md_to_pdf.py <input.md> <output.pdf> [--kicker "TEXT"] [--for "Name"]

The leading "# Title" block of the markdown (everything up to the first `---`)
becomes the cover page; every subsequent `#` heading starts a new page.

Requires: markdown, pygments, playwright (chromium).
"""
import sys, os, re, html, asyncio, argparse, datetime
import markdown as md_lib

ACCENT = "#c2703a"
ACCENT_DK = "#7a4a1e"

CSS = """
@page { size: A4; margin: 15mm 14mm 16mm 14mm; }
* { box-sizing: border-box; }
body {
  margin: 0; background: #fff; color: #1a1a1a;
  font-family: "DejaVu Sans", "Helvetica Neue", Arial, sans-serif;
  font-size: 9.9pt; line-height: 1.58;
  -webkit-print-color-adjust: exact; print-color-adjust: exact;
}
code, pre, .mono { font-family: "DejaVu Sans Mono", Consolas, monospace; }

/* ---------- cover ---------- */
.cover { height: 260mm; display: flex; flex-direction: column; justify-content: center;
  page-break-after: always; }
.cover .kicker { font-size: 9.6pt; letter-spacing: .22em; text-transform: uppercase;
  color: __ACCENT_DK__; font-weight: 700; margin-bottom: 10mm; }
.cover h1 { font-size: 33pt; line-height: 1.1; margin: 0 0 6mm 0; font-weight: 700;
  letter-spacing: -.5pt; border: 0; padding: 0; page-break-before: auto; }
.rule { height: 3px; background: __ACCENT__; width: 46mm; margin-bottom: 12mm; }
.cover .sub { font-size: 12.5pt; color: #4a5462; margin-bottom: 15mm; max-width: 132mm;
  line-height: 1.45; }
.facts { display: flex; gap: 13mm; margin-bottom: 16mm; }
.fact .n { font-size: 25pt; font-weight: 700; color: __ACCENT__; line-height: 1; }
.fact .l { font-size: 8.2pt; text-transform: uppercase; letter-spacing: .1em;
  color: #6b7280; margin-top: 2mm; }
.cover .foot { font-size: 8.8pt; color: #6b7280; border-top: 1px solid #dde1e6;
  padding-top: 5mm; line-height: 1.6; }
.cover .foot b { color: #1a1a1a; }

/* ---------- contents ---------- */
.toc { page-break-after: always; }
.toc h2.tochead { font-size: 19pt; margin: 0 0 7mm 0; color: #1a1a1a;
  border: 0; padding: 0; text-transform: none; letter-spacing: 0; }
.toc ul { list-style: none; margin: 0; padding: 0; }
.toc > ul > li { margin-bottom: 1.5mm; }
.toc .l1 { font-weight: 700; font-size: 10pt; color: __ACCENT_DK__;
  border-bottom: 1px solid #e6ded5; padding: 2mm 0 1.4mm 0; margin-top: 3.5mm; }
.toc .l2 { font-size: 8.9pt; color: #3d4653; padding: .9mm 0 .9mm 6mm; }

/* ---------- headings ---------- */
h1 { font-size: 20pt; font-weight: 700; margin: 0 0 6mm 0; padding-bottom: 3mm;
  border-bottom: 2.5px solid #1a1a1a; page-break-before: always; line-height: 1.2; }
h2 { font-size: 13pt; font-weight: 700; margin: 8mm 0 2.5mm 0; color: #1a1a1a;
  page-break-after: avoid; line-height: 1.3; }
h3 { font-size: 10.6pt; font-weight: 700; margin: 6mm 0 2mm 0; color: #33404f;
  page-break-after: avoid; }
h1 + h2, h1 + p { margin-top: 0; }

p { margin: 0 0 2.6mm 0; }
strong { font-weight: 700; }
hr { display: none; }

/* ---------- inline code ---------- */
p code, li code, td code, h2 code, h3 code, blockquote code {
  background: #f0f2f5; border: 1px solid #e0e4ea; border-radius: 3px;
  padding: 0 3px; font-size: 8.8pt; color: #1f3a5f; }

/* ---------- code blocks ---------- */
pre { background: #fbfbfc; border: 1px solid #e2e6eb; border-left: 3px solid __ACCENT__;
  border-radius: 4px; padding: 3.2mm 4mm; margin: 3mm 0; font-size: 7.9pt;
  line-height: 1.45; white-space: pre-wrap; word-break: break-word;
  page-break-inside: avoid; }
pre code { background: none; border: 0; padding: 0; font-size: inherit; color: inherit; }
/* unlabelled fences = ASCII diagrams */
pre.plain { background: #f7f8fa; border-left: 3px solid #c9d0d8; color: #33404f;
  font-size: 8.1pt; line-height: 1.35; }

/* ---------- tables ---------- */
table { width: 100%; border-collapse: collapse; margin: 3mm 0 4mm 0; font-size: 8.9pt;
  page-break-inside: avoid; }
th { background: #f6f2ee; color: __ACCENT_DK__; font-weight: 700; text-align: left;
  font-size: 8.3pt; text-transform: uppercase; letter-spacing: .06em;
  padding: 2.1mm 2.4mm; border-bottom: 1.5px solid #e0d5c8; }
td { padding: 1.9mm 2.4mm; border-bottom: 1px solid #edf0f3; vertical-align: top; }
tr:last-child td { border-bottom: 0; }

/* ---------- lists ---------- */
ul, ol { margin: 0 0 3mm 0; padding-left: 5.5mm; }
li { margin-bottom: 1.1mm; }

/* ---------- blockquote = rule callout ---------- */
blockquote { margin: 3.5mm 0; background: #fffaf3; border: 1px solid #f0e0c8;
  border-left: 3px solid #e0a955; border-radius: 4px; padding: 2.8mm 3.4mm;
  color: #4a3a24; font-size: 9.3pt; page-break-inside: avoid; }
blockquote p:last-child { margin-bottom: 0; }
blockquote code { background: #f6ecdb; border-color: #e8d8bd; color: #6b4a13; }

/* ---------- pygments, print-safe light ---------- */
.k, .kt, .kr, .kd, .kc { color: #a1152c; font-weight: 600; }
.c, .c1, .cm, .cs { color: #6f8a5a; font-style: italic; }
.cp, .cpf { color: #7c5aa8; }
.s, .s1, .s2, .sc { color: #1f6b34; }
.mi, .mf, .mh, .mo, .m { color: #b5651d; }
.n, .nx { color: #1a1a1a; }
.nf { color: #12518f; }
.nc { color: #12518f; font-weight: 600; }
.o, .p { color: #545c66; }
.nb { color: #7c5aa8; }
""".replace("__ACCENT_DK__", ACCENT_DK).replace("__ACCENT__", ACCENT)


def split_front_matter(text):
    """Pull the leading '# Title' block (up to the first ---) off the top."""
    lines = text.split("\n")
    if not lines or not lines[0].startswith("# "):
        return None, None, text
    title = lines[0][2:].strip()
    i = 1
    sub = []
    while i < len(lines) and lines[i].strip() != "---":
        if lines[i].strip():
            sub.append(lines[i].strip())
        i += 1
    return title, " ".join(sub), "\n".join(lines[i + 1:])


def build_toc(toc_tokens):
    out = ['<ul>']
    for t1 in toc_tokens:
        out.append(f'<li><div class="l1">{t1["name"]}</div>')   # already HTML-escaped by markdown
        if t1["children"]:
            out.append('<ul>')
            for t2 in t1["children"]:
                out.append(f'<li class="l2">{t2["name"]}</li>')
            out.append('</ul>')
        out.append('</li>')
    out.append('</ul>')
    return "".join(out)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("src"); ap.add_argument("dst")
    ap.add_argument("--kicker", default="Data Structures & Algorithms · C++")
    ap.add_argument("--owner", default="Hari")
    ap.add_argument("--note", default="")
    ap.add_argument("--patterns", default="12")
    ap.add_argument("--problems", default="33")
    a = ap.parse_args()

    raw = open(a.src, encoding="utf-8").read()
    title, subtitle, body_md = split_front_matter(raw)
    title = title or os.path.basename(a.src)

    md = md_lib.Markdown(extensions=["tables", "fenced_code", "codehilite", "toc",
                                     "sane_lists", "attr_list", "nl2br"],
                         extension_configs={
                             "codehilite": {"guess_lang": False, "noclasses": False,
                                            "css_class": "hl"},
                             "toc": {"toc_depth": "1-2"}})
    body = md.convert(body_md)

    # unlabelled fences -> ASCII-diagram styling
    body = re.sub(r'<pre>(?!<code class)', '<pre class="plain">', body)
    # codehilite wraps in <div class="hl"><pre>...</pre></div>; unwrap for cleaner CSS
    body = body.replace('<div class="hl">', '').replace('</div>\n\n<p>', '\n\n<p>')

    stats = [
        (str(body_md.count("\n## ")), "Sections"),
        (a.patterns, "Patterns"),
        (str(len(re.findall(r'```cpp', body_md))), "Code blocks"),
        (a.problems, "Problems"),
    ]
    facts = "".join(f'<div class="fact"><div class="n">{n}</div><div class="l">{l}</div></div>'
                    for n, l in stats)

    today = datetime.date.today().strftime("%d %B %Y")
    doc = f"""<!doctype html><html><head><meta charset="utf-8">
<title>{html.escape(title)}</title><style>{CSS}</style></head><body>

<div class="cover">
  <div class="kicker">{html.escape(a.kicker)}</div>
  <h1>{html.escape(title).replace(' — ', '<br>')}</h1>
  <div class="rule"></div>
  <div class="sub">{html.escape(subtitle or '')}</div>
  <div class="facts">{facts}</div>
  <div class="foot">
    Prepared for <b>{html.escape(a.owner)}</b> &middot; on-campus placement preparation<br>
    {a.note}Generated {today}
  </div>
</div>

<div class="toc"><h2 class="tochead">Contents</h2>{build_toc(md.toc_tokens)}</div>

{body}
</body></html>"""

    tmp_html = a.dst.replace(".pdf", ".html")
    open(tmp_html, "w", encoding="utf-8").write(doc)

    async def render():
        from playwright.async_api import async_playwright
        async with async_playwright() as pw:
            b = await pw.chromium.launch()
            pg = await b.new_page()
            await pg.goto("file://" + os.path.abspath(tmp_html))
            await pg.pdf(path=a.dst, format="A4", print_background=True,
                         display_header_footer=True, header_template="<div></div>",
                         footer_template=(
                             '<div style="width:100%;font-size:7pt;color:#9aa3ad;'
                             'font-family:Helvetica,Arial,sans-serif;padding:0 14mm;'
                             'display:flex;justify-content:space-between;">'
                             f'<span>{html.escape(title)}</span>'
                             '<span class="pageNumber"></span></div>'),
                         margin={"top": "15mm", "bottom": "16mm",
                                 "left": "14mm", "right": "14mm"})
            await b.close()

    asyncio.run(render())
    print(f"wrote {a.dst}")


if __name__ == "__main__":
    main()
