#!/usr/bin/env python3
"""
build_solved_pdf.py — build a "<Topic> — Solved Questions" PDF.

Single source of truth: the C++ code printed in the PDF is extracted verbatim
from a compiled-and-tested .cpp file, so the book can never drift from the code.

Usage:
    python3 build_solved_pdf.py <meta.json> <output.pdf>

meta.json:
{
  "title": "Trees & BST", "subtitle": "...", "kicker": "...",
  "source_cpp": "reference-part8-solutions.cpp",
  "footer": "...", "stats": [["38","Problems"], ...],
  "tiers": [{"name": "...", "blurb": "...",
             "problems": [{"id":"LC94","num":94,"title":"...","difficulty":"EASY",
                           "pattern":"...","problem":"...","approach":"...",
                           "complexity":"...","trap":"..."}]}]
}

Inline markup allowed in text fields: `code`, **bold**, *italic*.
Requires: pygments, playwright (chromium).
"""
import sys, os, re, json, html, asyncio, datetime
from pygments import highlight
from pygments.lexers import CppLexer
from pygments.formatters import HtmlFormatter

ACCENT, ACCENT_DK = "#c2703a", "#7a4a1e"

CSS = """
@page { size: A4; margin: 15mm 14mm 16mm 14mm; }
* { box-sizing: border-box; }
body { margin:0; background:#fff; color:#1a1a1a;
  font-family:"DejaVu Sans","Helvetica Neue",Arial,sans-serif;
  font-size:9.9pt; line-height:1.58;
  -webkit-print-color-adjust:exact; print-color-adjust:exact; }
code, pre { font-family:"DejaVu Sans Mono",Consolas,monospace; }

/* cover */
.cover { height:260mm; display:flex; flex-direction:column; justify-content:center;
  page-break-after:always; }
.cover .kicker { font-size:9.6pt; letter-spacing:.22em; text-transform:uppercase;
  color:__DK__; font-weight:700; margin-bottom:10mm; }
.cover h1 { font-size:33pt; line-height:1.1; margin:0 0 6mm 0; font-weight:700;
  letter-spacing:-.5pt; }
.rule { height:3px; background:__AC__; width:46mm; margin-bottom:12mm; }
.cover .sub { font-size:12.5pt; color:#4a5462; margin-bottom:15mm; max-width:132mm;
  line-height:1.45; }
.facts { display:flex; gap:13mm; margin-bottom:16mm; }
.fact .n { font-size:25pt; font-weight:700; color:__AC__; line-height:1; }
.fact .l { font-size:8.2pt; text-transform:uppercase; letter-spacing:.1em;
  color:#6b7280; margin-top:2mm; }
.cover .foot { font-size:8.8pt; color:#6b7280; border-top:1px solid #dde1e6;
  padding-top:5mm; line-height:1.6; }
.cover .foot b { color:#1a1a1a; }

/* contents */
.toc { page-break-after:always; }
.toc h2 { font-size:19pt; margin:0 0 7mm 0; }
.toc .tier { font-weight:700; font-size:10pt; color:__DK__;
  border-bottom:1px solid #e6ded5; padding:2mm 0 1.4mm 0; margin-top:4mm; }
.toc .row { font-size:8.9pt; color:#3d4653; padding:.9mm 0 .9mm 6mm; }
.toc .row .lc { display:inline-block; width:17mm; color:#8a949f; }

/* tier banner */
.tier-head { background:#fdf6ec; border:1px solid #f0e0c8; border-left:3px solid #e0a955;
  border-radius:4px; padding:4mm 4.5mm; margin:0 0 8mm 0; page-break-after:avoid;
  page-break-before:always; }
.toc + .tier-head { page-break-before:auto; }   /* the contents page already broke */
.tier-head h2 { margin:0 0 1.5mm 0; font-size:14pt; color:__DK__; }
.tier-head p { margin:0; font-size:9.2pt; color:#6b5c46; }

/* problem */
.prob { page-break-before:always; }
.tier-head + .prob { page-break-before:auto; }
.prob-head { border-bottom:2.5px solid #1a1a1a; padding-bottom:3mm; margin-bottom:5mm; }
.prob-head .idx { font-size:19pt; font-weight:700; color:#d9dde2; margin-right:3mm; }
.prob-head .name { font-size:15.5pt; font-weight:700; }
.prob-head .meta { margin-top:1.8mm; margin-left:12mm; font-size:8.4pt; color:#6b7280; }
.pill { display:inline-block; padding:.6mm 2mm; border-radius:3px; font-size:7.4pt;
  font-weight:700; letter-spacing:.08em; text-transform:uppercase; margin-right:2.5mm; }
.easy { background:#e8f3ea; color:#256b38; }
.medium { background:#fbeedd; color:#8a5a17; }
.hard { background:#f7e4e4; color:#8f2626; }

h3.sec { font-size:8.6pt; text-transform:uppercase; letter-spacing:.11em;
  color:#8a949f; font-weight:700; margin:5.5mm 0 2mm 0; page-break-after:avoid; }
p { margin:0 0 2.6mm 0; }

code { background:#f0f2f5; border:1px solid #e0e4ea; border-radius:3px;
  padding:0 3px; font-size:8.8pt; color:#1f3a5f; }

.cx { background:#fffaf3; border:1px solid #f0e0c8; border-left:3px solid #e0a955;
  border-radius:4px; padding:2.6mm 3.4mm; margin:3.5mm 0; font-size:9.2pt;
  color:#4a3a24; page-break-inside:avoid; }
.cx b { color:#1a1a1a; }
.trap { background:#fdf6ec; border:1px solid #f0e0c8; border-left:3px solid __AC__;
  border-radius:4px; padding:3mm 3.6mm; margin:4mm 0 0 0; page-break-inside:avoid; }
.trap .lbl { font-size:7.8pt; font-weight:700; letter-spacing:.11em; text-transform:uppercase;
  color:__AC__; margin-bottom:1.4mm; }
.trap p { margin:0; color:#4a3a24; font-size:9.3pt; }

pre { background:#fbfbfc; border:1px solid #e2e6eb; border-left:3px solid __AC__;
  border-radius:4px; padding:3.2mm 4mm; margin:2mm 0 0 0; font-size:7.9pt;
  line-height:1.45; white-space:pre-wrap; word-break:break-word; }
pre code { background:none; border:0; padding:0; font-size:inherit; color:inherit; }

/* pygments, print-safe light */
.k,.kt,.kr,.kd,.kc { color:#a1152c; font-weight:600; }
.c,.c1,.cm,.cs { color:#6f8a5a; font-style:italic; }
.cp,.cpf { color:#7c5aa8; }
.s,.s1,.s2,.sc { color:#1f6b34; }
.mi,.mf,.mh,.mo,.m { color:#b5651d; }
.n,.nx { color:#1a1a1a; }
.nf { color:#12518f; }
.nc { color:#12518f; font-weight:600; }
.o,.p { color:#545c66; }
.nb { color:#7c5aa8; }
""".replace("__DK__", ACCENT_DK).replace("__AC__", ACCENT)


def extract_blocks(cpp_path):
    """Pull every //>>>BEGIN ID ... //<<<END ID block out of the source file."""
    src = open(cpp_path, encoding="utf-8").read()
    out = {}
    for m in re.finditer(r'//>>>BEGIN (\S+)\n(.*?)//<<<END \1', src, re.S):
        out[m.group(1)] = m.group(2).rstrip("\n")
    return out


def inline(text):
    """Escape, then apply `code`, **bold**, *italic*."""
    t = html.escape(text)
    t = re.sub(r'`([^`]+)`', r'<code>\1</code>', t)
    t = re.sub(r'\*\*([^*]+)\*\*', r'<strong>\1</strong>', t)
    t = re.sub(r'(?<!\*)\*([^*]+)\*(?!\*)', r'<em>\1</em>', t)
    return t


def paras(text):
    return "".join(f"<p>{inline(p)}</p>" for p in text.split("\n\n") if p.strip())


def main():
    meta_path, dst = sys.argv[1], sys.argv[2]
    meta = json.load(open(meta_path, encoding="utf-8"))
    base = os.path.dirname(os.path.abspath(meta_path))
    blocks = extract_blocks(os.path.join(base, meta["source_cpp"]))
    fmt = HtmlFormatter(nowrap=True)

    toc, body = [], []
    n = 0
    for tier in meta["tiers"]:
        toc.append(f'<div class="tier">{inline(tier["name"])}</div>')
        body.append(f'<div class="tier-head"><h2>{inline(tier["name"])}</h2>'
                    f'<p>{inline(tier["blurb"])}</p></div>')
        for p in tier["problems"]:
            n += 1
            toc.append(f'<div class="row"><span class="lc">{n:02d}</span>'
                       f'LC {p["num"]} &middot; {inline(p["title"])}</div>')
            code = blocks.get(p["id"])
            if code is None:
                sys.exit(f"missing code block for {p['id']} in {meta['source_cpp']}")
            hl = highlight(code, CppLexer(), fmt)
            diff = p["difficulty"].lower()
            body.append(f"""
<div class="prob">
  <div class="prob-head">
    <span class="idx">{n:02d}</span><span class="name">LC {p['num']} &middot; {inline(p['title'])}</span>
    <div class="meta"><span class="pill {diff}">{html.escape(p['difficulty'])}</span>{inline(p['pattern'])}</div>
  </div>
  <h3 class="sec">Problem</h3>{paras(p['problem'])}
  <h3 class="sec">Approach</h3>{paras(p['approach'])}
  <div class="cx"><b>Complexity</b>&nbsp;&nbsp;{inline(p['complexity'])}</div>
  <h3 class="sec">C++ solution</h3>
  <pre><code>{hl}</code></pre>
  <div class="trap"><div class="lbl">Watch out</div><p>{inline(p['trap'])}</p></div>
</div>""")

    facts = "".join(f'<div class="fact"><div class="n">{html.escape(a)}</div>'
                    f'<div class="l">{html.escape(b)}</div></div>' for a, b in meta["stats"])
    title = f"{meta['title']} — Solved Questions"
    today = datetime.date.today().strftime("%d %B %Y")

    doc = f"""<!doctype html><html><head><meta charset="utf-8">
<title>{html.escape(title)}</title><style>{CSS}</style></head><body>
<div class="cover">
  <div class="kicker">{html.escape(meta['kicker'])}</div>
  <h1>{html.escape(meta['title'])}<br>Solved Questions</h1>
  <div class="rule"></div>
  <div class="sub">{html.escape(meta['subtitle'])}</div>
  <div class="facts">{facts}</div>
  <div class="foot">{meta['footer']}<br>Generated {today}</div>
</div>
<div class="toc"><h2>Contents</h2>{''.join(toc)}</div>
{''.join(body)}
</body></html>"""

    tmp = dst.replace(".pdf", ".html")
    open(tmp, "w", encoding="utf-8").write(doc)

    async def render():
        from playwright.async_api import async_playwright
        async with async_playwright() as pw:
            b = await pw.chromium.launch()
            pg = await b.new_page()
            await pg.goto("file://" + os.path.abspath(tmp))
            await pg.pdf(path=dst, format="A4", print_background=True,
                         display_header_footer=True, header_template="<div></div>",
                         footer_template=('<div style="width:100%;font-size:7pt;color:#9aa3ad;'
                                          'font-family:Helvetica,Arial,sans-serif;padding:0 14mm;'
                                          'display:flex;justify-content:space-between;">'
                                          f'<span>{html.escape(title)}</span>'
                                          '<span class="pageNumber"></span></div>'),
                         margin={"top": "15mm", "bottom": "16mm",
                                 "left": "14mm", "right": "14mm"})
            await b.close()

    asyncio.run(render())
    print(f"wrote {dst} ({n} problems)")


if __name__ == "__main__":
    main()
